#ifndef _ROM_SCRIPTING_UTIL_H_
#define _ROM_SCRIPTING_UTIL_H_

#if defined(__cplusplus)
extern "C" {
#endif

#include "script_api.h"

#define STACK_BUF_SZ 4096

/* Get a pointer to a global buffer of max size STACK_BUF_SZ containing
   a stringified representation of the current stack for the script */
const char * scutil_get_stack_strp(script_t *pS);

#if defined(__cplusplus)
}
#endif

#endif
