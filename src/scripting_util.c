#include "scripting_util.h"
#include "scripting.h"

#include <lauxlib.h>

#include <string.h>

static char stack_buf[STACK_BUF_SZ] = {0};

const char *scutil_get_stack_strp(script_t *pS)
{
    int top      = lua_gettop(pS);
    stack_buf[0] = 0;

    char *p     = stack_buf;
    int   space = STACK_BUF_SZ - 1;
    int   len   = 0;

    for (int i = 1; i <= top; i++) {
        int t = lua_type(pS, i);
        switch (t) {
        case LUA_TSTRING:
            len += snprintf(p + len, space - len, "%d:\"%.10s...\"  ", i, lua_tostring(pS, i));
            break;
        case LUA_TBOOLEAN:
            len += snprintf(p + len, space - len, "%d:%s  ", i,
                            lua_toboolean(pS, i) ? "true" : "false");
            break;
        case LUA_TNUMBER:
            if (lua_isinteger(pS, i))
                len += snprintf(p + len, space - len, "%d:%lld  ", i, lua_tointeger(pS, i));
            else
                len += snprintf(p + len, space - len, "%d:%g  ", i, lua_tonumber(pS, i));
            break;
        default:
            len += snprintf(p + len, space - len, "%d:%s  ", i, lua_typename(pS, t));
            break;
        }
    }

    stack_buf[len - 2] = 0;

    return stack_buf;
}
