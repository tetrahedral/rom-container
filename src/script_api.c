#include "script_api.h"
#include "scripting.h"

#include <lua.h>
#include <lauxlib.h>

#include <string.h>

#include "merc.h"


#define SID_UV_IDX 1


static script_id_t get_script_id(script_t *pS);


/*
 * Send a string to a character.
 * stack: 1 - string to send
 *        2 - character to send to
 */
static SCRIPT_API(sapi_send_char)
{
    script_id_t id = get_script_id(pS);

    const char *str = luaL_checkstring(pS, 1);

    luaL_checktype(pS, 2, LUA_TLIGHTUSERDATA);

    CHAR_DATA *ch = (CHAR_DATA *)lua_touserdata(pS, 2);
    if (ch == NULL) {
        script_rec_err(id);
        lua_settop(pS, 0);
        lua_pushliteral(pS, "invalid character data");
        return 1;
    }

    send_to_char(str, ch);

    lua_settop(pS, 0);
    return 0;
}

/*
 * Register this script as handling a do_<command>.
 * stack: 1 - command name
 *        2 - name of lua function to call
 */
static SCRIPT_API(sapi_reg_do)
{
    const char *cmd = luaL_checkstring(pS, 1);
    luaL_checktype(pS, 2, LUA_TFUNCTION);

    script_id_t id = get_script_id(pS);

    /* creates a ref in the registry for the function on the stack */
    int funcref = luaL_ref(pS, LUA_REGISTRYINDEX);

    int rc = script_reg_do_cmd(id, cmd, funcref);
    if (rc != S_OK) {
        script_rec_err(id);
        lua_settop(pS, 0);
        lua_pushliteral(pS, "error registering command handler");
        return 1;
    }

    lua_settop(pS, 0);
    return 0;
}

/*
 * Scripts can use mud.log(...) to add messages to the mud log.
 */
static SCRIPT_API(sapi_log)
{
    script_id_t id = get_script_id(pS);

    char buf[MAX_STRING_LENGTH];
    buf[0] = 0;

    int         argc = lua_gettop(pS);
    const char *str;

    for (int i = 1; i <= argc; i++) {
        str = luaL_checkstring(pS, i);
        strncat(buf, str, MAX_STRING_LENGTH - strlen(buf) - 1);
    }

    script_log(id, buf);

    lua_settop(pS, 0);
    return 0;
}

script_api_t script_api_list[] = {
    {  "send_char", sapi_send_char},
    {"register_do",    sapi_reg_do},
    {        "log",       sapi_log},
    {         NULL,           NULL}
};

/* Register the global scripting api with a script */
int mud_script_register_api(script_t *pS, script_id_t script_id)
{
    luaL_checkversion(pS);

    /* Create table for script api functions as global "mud" */
    luaL_newlibtable(pS, script_api_list);

    /* Set script_id as first upvalue to every api function */
    lua_pushlightuserdata(pS, (void *)script_id);
    luaL_setfuncs(pS, script_api_list, 1);
    lua_setglobal(pS, "mud");

    return S_OK;
}

/*
 * Get the script id associated with this state, when called from within a script.
 */
static script_id_t get_script_id(script_t *pS)
{
    int sIdIdx = lua_upvalueindex(SID_UV_IDX);

    if (lua_islightuserdata(pS, sIdIdx))
        return (script_id_t)lua_touserdata(pS, sIdIdx);

    return -1;
}

int mud_script_call_func(script_t *pS, const char *func)
{
    lua_getglobal(pS, func);

    if (!lua_isfunction(pS, -1))
        return S_INVALID_CALL;

    if (lua_pcall(pS, 0, 0, 0) != LUA_OK) {
        script_rec_err(get_script_id(pS));
        return S_EXE_ERR;
    }

    return S_OK;
}

int mud_script_do_cmd(script_t *pS, int funcref, void *ch, const char *argument)
{
    if (lua_rawgeti(pS, LUA_REGISTRYINDEX, funcref) != LUA_TFUNCTION)
        return S_INVALID_CALL;

    lua_pushlightuserdata(pS, ch);
    lua_pushstring(pS, argument);

    if (lua_pcall(pS, 2, 0, 0) != LUA_OK) {
        script_rec_err(get_script_id(pS));
        return S_EXE_ERR;
    }

    return S_OK;
}
