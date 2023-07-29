#include <stdarg.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <dirent.h>

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

#include "scripting.h"
#include "script_api.h"
#include "merc.h"

#define MAX_SCRIPTS 256
#define ERR_BUF_SZ  1024

#define SCRIPT_EXT  ".lua"
#define SCRIPTS_DIR "../scripts/"
#define ERR_LOG_PFX "[*****] BUG: "

struct script_data {
    char      *filename;
    lua_State *lState;
};

typedef struct script_data SCRIPT_DATA;

static SCRIPT_DATA scripts[MAX_SCRIPTS] = {0};

static bool initialized = false;

static size_t loaded_scripts = 0;

static char error_buf[ERR_BUF_SZ] = {'\0'};

static const luaL_Reg lualibs[] = {
    {         "base",   luaopen_base},
    { LUA_TABLIBNAME,  luaopen_table},
    { LUA_STRLIBNAME, luaopen_string},
    {LUA_UTF8LIBNAME,   luaopen_utf8},
    {LUA_MATHLIBNAME,   luaopen_math},
    {           NULL,           NULL}
};

static void log_errf(const char *str, ...)
{
    va_list v_args;

    strcpy(error_buf, ERR_LOG_PFX);

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

static void openlibs(lua_State *l)
{
    const luaL_Reg *lib;
    for (lib = lualibs; lib->func != NULL; lib++) {
        lib->func(l);
        lua_settop(l, 0);
    }
}

static int register_script_api(lua_State *lState)
{
    SCRIPT_API_ENTRY *api_entry;

    for (api_entry = script_api_list; api_entry->name != NULL; api_entry++)
        lua_register(lState, api_entry->name, api_entry->func);

    return S_OK;
}

static int load_script(char *filename)
{
    size_t     sIdx = loaded_scripts;
    lua_State *lState;

    if (loaded_scripts >= MAX_SCRIPTS) {
        log_errf("load_script: unable to load all scripts; MAX_SCRIPTS reached");
        return S_MAX_SCRIPTS;
    }

    lState = luaL_newstate();
    openlibs(lState);

    scripts[sIdx].filename = filename;
    scripts[sIdx].lState   = lState;

    if (luaL_dofile(lState, filename) != LUA_OK) {
        log_errf("error loading script [%s]: %s", filename, luaL_checkstring(lState, 1));
        lua_pop(lState, 1);
        lua_close(lState);
        return S_LOAD_ERR;
    }

    loaded_scripts++;
    return S_OK;
}

/*
 * Scan the SCRIPTS_DIR directory looking for files ending with
 * the SCRIPT_EXT extension.
 */
static int scan_scripts(void)
{
    DIR           *dir;
    struct dirent *ent;
    char           script_path[512];
    size_t         fname_len;

    log_strf("scan_scripts: beginning scan of " SCRIPTS_DIR);

    if ((dir = opendir(SCRIPTS_DIR)) == NULL) {
        log_errf("scan_scripts: unable to open script directory '" SCRIPTS_DIR "': %s",
                 strerror(errno));
        return S_DIR_ERR;
    }

    int rc;

    while ((ent = readdir(dir)) != NULL) {
        if (ent->d_type != DT_REG)
            continue;

        fname_len = strlen(ent->d_name);

        if (fname_len < 4)
            continue;

        if (strcmp(ent->d_name + fname_len - 4, SCRIPT_EXT) != 0)
            continue;

        snprintf(script_path, sizeof(script_path), SCRIPTS_DIR "%s", ent->d_name);

        if ((rc = load_script(script_path)) != S_OK)
            break;
    }

    closedir(dir);

    return rc;
}

/* Initialize the scripting runtime, loading all scripts under SCRIPT_DIR. */
int script_rt_init()
{
    int rc = S_OK;

    if (initialized)
        return S_OK;

    log_strf("initializing script runtime");

    if ((rc = scan_scripts()) == S_OK)
        initialized = true;

    return rc;
}

/* Shut down the scripting runtime, safely closing all loaded scripts. */
void script_rt_close()
{
    log_strf("closing script runtime");

    for (size_t i = 0; i < loaded_scripts; i++) {
        if (scripts[i].lState == NULL)
            continue;
        lua_close(scripts[i].lState);
    }
}
