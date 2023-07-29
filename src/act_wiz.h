#ifndef _ROM_ACT_WIZ_H_
#define _ROM_ACT_WIZ_H_

#if defined(__cplusplus)
extern "C" {
#endif

#include <stdbool.h>

struct char_data;
struct obj_data;

bool obj_check(struct char_data *ch, struct obj_data *obj);
void recursive_clone(struct char_data *ch, struct obj_data *obj,
                     struct obj_data *clone);

#if defined(__cplusplus)
}
#endif

#endif /* _ROM_ACT_WIZ_H_ */