#ifndef _ROM_BIT_H_
#define _ROM_BIT_H_

#include <stdbool.h>

struct flag_type;

bool is_stat(const struct flag_type *flag_table);
int flag_value(const struct flag_type *flag_table, char *argument);
char *flag_string(const struct flag_type *flag_table, int bits);

#endif
