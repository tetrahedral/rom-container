#ifndef _ROM_SCRIPT_API_H_
#define _ROM_SCRIPT_API_H_

#if defined(__cplusplus)
extern "C" {
#endif

#include <lua.h>

#define SCRIPT_API(name) int name(lua_State *lState)

struct script_api_entry {
    const char     *name;
    lua_CFunction  func;
};

typedef struct script_api_entry SCRIPT_API_ENTRY;

extern SCRIPT_API_ENTRY script_api_list[];

#if defined(__cplusplus)
}
#endif

#endif /* _ROM_SCRIPT_API_H_ */
