#ifndef _ROM_BAN_H_
#define _ROM_BAN_H_

#if defined(__cplusplus)
extern "C" {
#endif

#include <stdbool.h>

struct char_data;

void save_bans(void);
void load_bans(void);
bool check_ban(char *site, int type);
void ban_site(struct char_data *ch, char *argument, bool fPerm);
void do_ban(struct char_data *ch, char *argument);
void do_permban(struct char_data *ch, char *argument);
void do_allow(struct char_data *ch, char *argument);

#if defined(__cplusplus)
}
#endif

#endif /* _ROM_BAN_H_ */
