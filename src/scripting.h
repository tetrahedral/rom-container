#ifndef _ROM_SCRIPTING_H_
#define _ROM_SCRIPTING_H_

#if defined(__cplusplus)
extern "C" {
#endif

int  script_rt_init(void);  /* initialize the scripting runtime */
void script_rt_close(void); /* shut down the scripting runtime */

#if defined(__cplusplus)
}
#endif

#endif /* _ROM_SCRIPTING_H_ */
