#ifndef _ROM_SCRIPT_API_H_
#define _ROM_SCRIPT_API_H_

/*
 * API between the mud scripting runtime and individual script instances.
 *
 * Functions beginning with "mud_script_" are for use by the scripting runtime to interact
 * with a particular script instance.
 *
 * Non-scripting-runtime areas of mud code should use the API provided by the scripting
 * runtime itself by including "scripting.h"
 */

#if defined(__cplusplus)
extern "C" {
#endif

#include "scripting.h"

#define SCRIPT_EVENT_INIT  "on_init"
#define SCRIPT_EVENT_CLOSE "on_close"

#define SCRIPT_API(name) int name(script_t *pS)

typedef struct lua_State script_t;
typedef long             script_id_t;
typedef struct luaL_Reg  script_api_t;

/*
 * mud_script_* functions are the interface from the mud into a script.
 */
int mud_script_register_api(script_t *pS, script_id_t script_id);
int mud_script_call_func(script_t *pS, const char *func);
int mud_script_do_cmd(script_t *pS, int funcref, void *ch, const char *argument);

/*
 * script_* functions are the interface from a script into the mud.
 */
void script_log(script_id_t id, const char *str);
void script_rec_err(script_id_t id); /* record an error */
int  script_reg_do_cmd(script_id_t id, const char *cmd, int funcref);

#if defined(__cplusplus)
}
#endif

#endif /* _ROM_SCRIPT_API_H_ */
