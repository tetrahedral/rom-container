#include "scripting.h"
#include "script_api.h"
#include "scripting_util.h"

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

#include <stdarg.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <dirent.h>

#include "merc.h"


#define DBGF(fmt, ...) \
    log_strf("DBG " __FILE__ ":%d [%s] " fmt, __LINE__, __func__ __VA_OPT__(, ) __VA_ARGS__)
#define DBG(fmt) DBGF(fmt, 0)

#define LOGF(fmt, ...) \
    log_strf(__FILE__ ":%d [%s] " fmt, __LINE__, __func__ __VA_OPT__(, ) __VA_ARGS__)
#define LOG(fmt) LOGF(fmt, 0)

#define LOGERRF(fmt, ...) \
    log_errf(__FILE__ ":%d [%s] " fmt, __LINE__, __func__ __VA_OPT__(, ) __VA_ARGS__)
#define LOGERR(fmt) LOGERRF(fmt, 0)


#define freenclr(p) \
    do {            \
        free(p);    \
        p = NULL;   \
    } while (0)


#define SCRIPT_EXT  ".lua"
#define SCRIPTS_DIR "../scripts/"
#define MAX_SCRIPTS 256

#define ERR_LOG_PFX "[*****] BUG: "
#define ERR_BUF_SZ  1024

#define MAX_CMD_LEN 40


typedef struct script_data   script_data_t;
typedef struct script_do_cmd script_do_cmd_t;

struct script_do_cmd {
    script_do_cmd_t *next;
    int              funcref;
    char             cmd[MAX_CMD_LEN];
};

struct script_data {
    script_id_t      id;
    script_t        *pS;
    char            *filename;
    char            *name;
    char            *version;
    char            *author;
    char            *description;
    size_t           errct;
    script_do_cmd_t *do_cmds;
};


static script_data_t scripts[MAX_SCRIPTS] = {0};
static script_id_t   loaded_scripts       = 0;
static bool          initialized          = false;


static int reg_script_by_table(script_id_t id);


static void log_errf(const char *str, ...)
{
    static char error_buf[ERR_BUF_SZ] = {'\0'};

    strcpy(error_buf, ERR_LOG_PFX);

    va_list v_args;
    va_start(v_args, str);
    vsnprintf(error_buf + strlen(error_buf), sizeof(error_buf), str, v_args);
    va_end(v_args);

    log_string(error_buf);
}

static void log_strf(const char *str, ...)
{
    va_list v_args;
    char    buf[MAX_STRING_LENGTH];

    va_start(v_args, str);
    vsnprintf(buf, sizeof(buf), str, v_args);
    va_end(v_args);

    log_string(buf);
}

static void script_close(script_id_t id)
{
    if (scripts[id].pS == NULL)
        return;

    LOGF("closing script id=%d name=%s", id, scripts[id].name);

    mud_script_call_func(scripts[id].pS, SCRIPT_EVENT_CLOSE);

    script_do_cmd_t *cmd = scripts[id].do_cmds;
    while (cmd != NULL) {
        script_do_cmd_t *next = cmd->next;
        free(cmd);
        cmd = next;
    }

    lua_close(scripts[id].pS);

    scripts[id].pS    = NULL;
    scripts[id].errct = 0;

    freenclr(scripts[id].filename);
    freenclr(scripts[id].name);
    freenclr(scripts[id].version);
    freenclr(scripts[id].author);
    freenclr(scripts[id].description);
}

static int openlibs(script_t *pS)
{
    static const script_api_t lualibs[] = {
        {         "base",    luaopen_base},
        { LUA_TABLIBNAME,   luaopen_table},
        {  LUA_IOLIBNAME,      luaopen_io},
        { LUA_STRLIBNAME,  luaopen_string},
        {LUA_UTF8LIBNAME,    luaopen_utf8},
        {LUA_MATHLIBNAME,    luaopen_math},
        {LUA_LOADLIBNAME, luaopen_package},
        {           NULL,            NULL}
    };

    for (const script_api_t *lib = lualibs; lib->func != NULL; lib++) {
        luaL_requiref(pS, lib->name, lib->func, true);
        if (lua_type(pS, -1) != LUA_TTABLE) {
            LOGERRF("unable to open library [%s]", lib->name);
            lua_settop(pS, 0);
            return S_LOAD_ERR;
        }
        lua_settop(pS, 0);
    }
    return S_OK;
}

static int load_script(char *filename)
{
    script_id_t sIdx = loaded_scripts;

    LOGF("loading script id=%d file=%s", sIdx, filename);

    if (sIdx >= MAX_SCRIPTS) {
        LOGERR("load_script: unable to load all scripts; MAX_SCRIPTS reached");
        return S_MAX_SCRIPTS;
    }

    lua_State *pS = luaL_newstate();

    int rc = openlibs(pS);
    if (rc != S_OK) {
        lua_close(pS);
        return rc;
    }

    rc = mud_script_register_api(pS, sIdx);
    if (rc != S_OK) {
        lua_close(pS);
        return rc;
    }

    scripts[sIdx].id       = sIdx;
    scripts[sIdx].filename = malloc(strlen(filename) + 1);
    strcpy(scripts[sIdx].filename, filename);
    scripts[sIdx].pS      = pS;
    scripts[sIdx].errct   = 0;
    scripts[sIdx].do_cmds = NULL;

    loaded_scripts++;

    rc = luaL_dofile(pS, filename);
    if (rc != LUA_OK) {
        LOGERRF("error loading script [%s]: %d %s", filename, rc, lua_tostring(pS, -1));
        lua_settop(pS, 0);
        script_close(sIdx);
        loaded_scripts--;
        return S_LOAD_ERR;
    }

    if (lua_istable(pS, -1))
        reg_script_by_table(sIdx);

    lua_settop(pS, 0);

    rc = mud_script_call_func(pS, SCRIPT_EVENT_INIT);
    if (rc != S_INVALID_CALL && rc != S_OK) {
        LOGERRF("on_init failed [%s]: %d %s", filename, rc, lua_tostring(pS, -1));
    }

    lua_settop(pS, 0);

    return S_OK;
}

/*
 * Scan the SCRIPTS_DIR directory looking for files ending with
 * the SCRIPT_EXT extension.
 */
static int scan_scripts(void)
{
    LOG("beginning scan of " SCRIPTS_DIR);

    DIR *dir = opendir(SCRIPTS_DIR);
    if (dir == NULL) {
        LOGERRF("unable to open script directory '" SCRIPTS_DIR "': %s", strerror(errno));
        return S_DIR_ERR;
    }

    int rc;

    struct dirent *ent = readdir(dir);

    while ((ent = readdir(dir)) != NULL) {
        if (ent->d_type != DT_REG)
            continue;

        size_t fname_len = strlen(ent->d_name);

        if (fname_len < 4)
            continue;

        if (strcmp(ent->d_name + fname_len - 4, SCRIPT_EXT) != 0)
            continue;

        char script_path[512];
        snprintf(script_path, sizeof(script_path), SCRIPTS_DIR "%s", ent->d_name);

        rc = load_script(script_path);
        if (rc != S_OK)
            break;
    }

    closedir(dir);

    return rc;
}

/* Initialize the scripting runtime, loading all scripts under SCRIPT_DIR. */
int init_scripting_runtime(void)
{
    if (initialized)
        return S_OK;

    LOG("initializing script runtime");

    int rc = scan_scripts();
    if (rc == S_OK)
        initialized = true;

    return rc;
}

/* Shut down the scripting runtime, safely closing all loaded scripts. */
void close_scripting_runtime(void)
{
    LOG("closing script runtime");

    for (script_id_t i = 0; i < loaded_scripts; i++)
        script_close(i);

    loaded_scripts = 0;
    initialized    = false;
}

/*
 * Given cmd, look for a script that has registered a do_cmd for it, and invoke it
 * if found. Return S_NO_SCRIPT if no script has registered a do_cmd for cmd.
 */
int do_scriptcmd(char *cmd, CHAR_DATA *ch, char *argument)
{
    for (script_id_t id = 0; id < loaded_scripts; id++) {
        script_do_cmd_t *pCmd = scripts[id].do_cmds;
        while (pCmd != NULL) {
            if (strcmp(pCmd->cmd, cmd) == 0) {
                mud_script_do_cmd(scripts[id].pS, pCmd->funcref, ch, argument);
                return S_OK;
            }
            pCmd = pCmd->next;
        }
    }
    return S_NO_SCRIPT;
}

/* exec for script logging */
void script_log(script_id_t id, const char *str)
{
    if (id < 0 || id >= MAX_SCRIPTS)
        return;

    if (scripts[id].pS == NULL)
        return;

    LOGF("%s[%d]: %s", scripts[id].name, id, str);
}

/* For script CFuncs to record errors */
void script_rec_err(script_id_t id)
{
    if (id < 0 || id >= loaded_scripts)
        return;

    scripts[id].errct += 1;
}

/* exec for scripts programmatic do_cmd registering */
int script_reg_do_cmd(script_id_t id, const char *cmd, int funcref)
{
    if (id < 0 || id >= loaded_scripts)
        return S_OK;

    script_do_cmd_t *new_do_cmd = malloc(sizeof(script_do_cmd_t));

    new_do_cmd->cmd[0] = 0;
    strncpy(new_do_cmd->cmd, cmd, MAX_CMD_LEN - 1);

    new_do_cmd->funcref         = funcref;

    if (scripts[id].do_cmds == NULL) {
        scripts[id].do_cmds = new_do_cmd;
    } else {
        script_do_cmd_t *pCmds = scripts[id].do_cmds;
        while (pCmds->next != NULL)
            pCmds = pCmds->next;
        pCmds->next = new_do_cmd;
    }

    return S_OK;
}


/*
Load any help files the script wants to add.
Metadata table: {
    helps = {
        { level = 0, keywords = "foo", text = "bar" },
        { level = 0, keywords = "baz", text = "quux" },
        ...
    }
}
*/
static void reg_script_helps(script_id_t id, script_t *pS)
{
    DBGF("reg_script_helps: %s: %s", scripts[id].name, scutil_get_stack_strp(pS));

    int t = lua_gettop(pS);

    if (lua_getfield(pS, t, "helps") != LUA_TTABLE) {
        LOGF("no helps to load: %s", scripts[id].name);
        lua_pop(pS, 1);
        return;
    }

    lua_len(pS, -1);
    lua_Integer helps_len = lua_tointeger(pS, -1);
    lua_pop(pS, 1);

    for (lua_Integer i = 1; i <= helps_len; i++) {
        if (lua_geti(pS, -1, i) != LUA_TTABLE) {
            LOGERRF("helps[%d] must a table: %s", i, scripts[id].name);
            DBGF("stack: %s", scutil_get_stack_strp(pS));
            lua_pop(pS, 1);
            continue;
        }

        int t_help = lua_gettop(pS);

        if (lua_getfield(pS, t_help, "level") != LUA_TNUMBER) {
            LOGERRF("helps[%d].level must be a number: %s", i, scripts[id].name);
            DBGF("stack: %s", scutil_get_stack_strp(pS));
            lua_pop(pS, 2);
            continue;
        }

        lua_Integer help_level = lua_tointeger(pS, -1);
        lua_pop(pS, 1);

        if (lua_getfield(pS, t_help, "keywords") != LUA_TSTRING) {
            LOGERRF("helps[%d].keywords must be a string: %s", i, scripts[id].name);
            DBGF("stack: %s", scutil_get_stack_strp(pS));
            lua_pop(pS, 2);
            continue;
        }

        const char *keywords = lua_tostring(pS, -1);

        if (lua_getfield(pS, t_help, "text") != LUA_TSTRING) {
            LOGERRF("helps[%d].text must be a string: %s", i, scripts[id].name);
            DBGF("stack: %s", scutil_get_stack_strp(pS));
            lua_pop(pS, 3);
            continue;
        }

        const char *helptext = lua_tostring(pS, -1);

        HELP_DATA *pHelp = alloc_perm(sizeof(*pHelp));
        pHelp->level     = (sh_int)help_level;
        pHelp->keyword   = strdup(keywords);
        pHelp->text      = strdup(helptext);

        if (help_first == NULL)
            help_first = pHelp;
        if (help_last != NULL)
            help_last->next = pHelp;

        help_last   = pHelp;
        pHelp->next = NULL;
        top_help++;

        lua_pop(pS, 3);
    }

    lua_pop(pS, 1);
}

/*
Register a script using data returned in a metadata table from the script's initialization.

table = {
    name = "scriptname",
    description = "script description",
    commands = {
        cmdname = { "do_funcname", "help_funcname" }
    }
}
 */
static int reg_script_by_table(script_id_t id)
{
    script_t *pS = scripts[id].pS;

    /* t is the script metadata table */
    int t = lua_gettop(pS);

    if (lua_getfield(pS, t, "name") == LUA_TSTRING) {
        scripts[id].name = strdup(lua_tostring(pS, -1));
        DBGF("script name: '%s'", scripts[id].name);
    }
    lua_pop(pS, 1);

    if (lua_getfield(pS, t, "version") == LUA_TSTRING) {
        scripts[id].version = strdup(lua_tostring(pS, -1));
        DBGF("script version: '%s'", scripts[id].version);
    }
    lua_pop(pS, 1);

    if (lua_getfield(pS, t, "description") == LUA_TSTRING) {
        scripts[id].description = strdup(lua_tostring(pS, -1));
        DBGF("script description: '%s'", scripts[id].description);
    }
    lua_pop(pS, 1);

    if (lua_getfield(pS, t, "author") == LUA_TSTRING) {
        scripts[id].author = strdup(lua_tostring(pS, -1));
        DBGF("script author: '%s'", scripts[id].author);
    }
    lua_pop(pS, 1);

    if (lua_getfield(pS, t, "commands") != LUA_TTABLE) {
        LOGERR("expected 'commands' key to be a table");
        DBGF("stack: %s", scutil_get_stack_strp(pS));
        lua_pop(pS, 1);
        return S_OK;
    }

    /* ct is the commands table */
    int ct = lua_gettop(pS);

    lua_pushnil(pS); /* lua_next() init */

    while (lua_next(pS, ct) != 0) {
        /* key */
        if (!lua_isstring(pS, -2)) {
            LOGF("script '%s' commands table: skipping invalid key", scripts[id].name);
            lua_pop(pS, 1); /* leave key on stack for lua_next() */
            continue;
        }

        /* value */
        if (lua_isstring(pS, -1)) {
            /* value is the name of the handler function */
            lua_getglobal(pS, lua_tostring(pS, -1));
            lua_remove(pS, -2); /* remove function name from stack */
        }

        if (lua_type(pS, -1) != LUA_TFUNCTION) {
            LOGF("'%s' command '%s': function not found", scripts[id].name, lua_tostring(pS, -2));
            lua_pop(pS, 1); /* leave key on stack for lua_next() */
            continue;
        }

        /* creates a ref in the registry for the function on the stack */
        int funcref = luaL_ref(pS, LUA_REGISTRYINDEX);

        /* key is the command name */
        const char *cmd = lua_tostring(pS, -1);

        /* register the command */
        script_reg_do_cmd(id, cmd, funcref);

        LOGF("'%s' registered command '%s'", scripts[id].name, cmd);
    }

    lua_pop(pS, 1); /* pop commands table */

    reg_script_helps(id, pS);

    lua_settop(pS, 0);

    return S_OK;
}
