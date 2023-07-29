#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

#include "script_api.h"
#include "merc.h"

static SCRIPT_API(script_send_char) {
    const char *str = luaL_checkstring(lState, 1);

    if (str == NULL)
        return LUA_ERRRUN;

    CHAR_DATA *ch = (CHAR_DATA *)lua_touserdata(lState, 2);

    if (ch == NULL)
        return LUA_ERRRUN;

    send_to_char(str, ch);

    return LUA_OK;
}

SCRIPT_API_ENTRY script_api_list[] = {
    {"send_char", script_send_char},
    {       NULL,             NULL}
};
