#ifndef _ROM_SCRIPTING_H_
#define _ROM_SCRIPTING_H_

#if defined(__cplusplus)
extern "C" {
#endif

#define S_OK          0
#define S_DIR_ERR     1
#define S_EXE_ERR     2
#define S_MAX_SCRIPTS 3
#define S_LOAD_ERR    4
#define S_API_ERR     5

int  script_rt_init(void);  /* initialize the scripting runtime */
void script_rt_close(void); /* shut down the scripting runtime */

#if defined(__cplusplus)
}
#endif

#endif /* _ROM_SCRIPTING_H_ */
