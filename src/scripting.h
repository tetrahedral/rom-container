#ifndef _ROM_SCRIPTING_H_
#define _ROM_SCRIPTING_H_

#if defined(__cplusplus)
extern "C" {
#endif

#include "merc.h"

#define S_OK           0
#define S_DIR_ERR      1
#define S_EXE_ERR      2
#define S_MAX_SCRIPTS  3
#define S_LOAD_ERR     4
#define S_API_ERR      5
#define S_INVALID_CALL 6
#define S_NO_SCRIPT    7

/*
 * interface from mud into the scripting runtime
 */
int  init_scripting_runtime(void);
void close_scripting_runtime(void);
int  do_scriptcmd(char *cmd, CHAR_DATA *ch, char *argument);

#if defined(__cplusplus)
}
#endif

#endif /* _ROM_SCRIPTING_H_ */
