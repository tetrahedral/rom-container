#ifndef _ROM_DB_H_
#define _ROM_DB_H_

/***************************************************************************
 *  Original Diku Mud copyright (C) 1990, 1991 by Sebastian Hammer,	   *
 *  Michael Seifert, Hans Henrik St{rfeldt, Tom Madsen, and Katja Nyboe.   *
 *									   *
 *  Merc Diku Mud improvments copyright (C) 1992, 1993 by Michael	   *
 *  Chastain, Michael Quan, and Mitchell Tse.				   *
 *									   *
 *  In order to use any part of this Merc Diku Mud, you must comply with   *
 *  both the original Diku license in 'license.doc' as well the Merc	   *
 *  license in 'license.txt'.  In particular, you may not remove either of *
 *  these copyright notices.						   *
 *									   *
 *  Much time and thought has gone into this software and you are	   *
 *  benefitting.  We hope that you share your changes too.  What goes	   *
 *  around, comes around.						   *
 ***************************************************************************/

/***************************************************************************
 *	ROM 2.4 is copyright 1993-1998 Russ Taylor			   *
 *	ROM has been brought to you by the ROM consortium		   *
 *	    Russ Taylor (rtaylor@hypercube.org)				   *
 *	    Gabrielle Taylor (gtaylor@hypercube.org)			   *
 *	    Brian Moore (zump@rom.org)					   *
 *	By using this code, you have agreed to follow the terms of the	   *
 *	ROM license, in the file Rom24/doc/rom.license			   *
 ***************************************************************************/

#include "merc.h"

/* vals from db.c */
extern bool            fBootDb;
extern int             newmobs;
extern int             newobjs;
extern MOB_INDEX_DATA *mob_index_hash[MAX_KEY_HASH];
extern OBJ_INDEX_DATA *obj_index_hash[MAX_KEY_HASH];
extern int             top_mob_index;
extern int             top_obj_index;
extern int             top_affect;
extern int             top_ed;
extern AREA_DATA      *area_first;


/* from db2.c */
extern int social_count;

/* conversion from db.h */
void convert_mob(MOB_INDEX_DATA *mob);
void convert_obj(OBJ_INDEX_DATA *obj);

void bug_area(const char *str, int param, FILE *fp,
              const char *area_str);  /* report a bug in an area file */
void bug(const char *str, int param); /* report a bug */

/* macro for flag swapping */
#define GET_UNSET(flag1, flag2) (~(flag1) & ((flag1) | (flag2)))

/* Magic number for memory allocation */
#define MAGIC_NUM 52571214

/* inserted for OLC */
/* func from db.c */
extern void assign_area_vnum(int vnum); /* OLC */


/*
 * Local booting procedures.
 */
void init_mm(void);
void load_area(FILE *fp);
void new_load_area(FILE *fp); /* OLC */
void load_helps(FILE *fp);
void load_old_mob(FILE *fp);
void load_mobiles(FILE *fp);
void load_old_obj(FILE *fp);
void load_objects(FILE *fp);
void load_resets(FILE *fp);
void load_rooms(FILE *fp);
void load_shops(FILE *fp);
void load_socials(FILE *fp);
void load_specials(FILE *fp);
void load_notes(void);
void load_bans(void);

void fix_exits(void);

void reset_area(AREA_DATA *pArea);


/* from db2.c */

void convert_mobile(MOB_INDEX_DATA *pMobIndex); /* OLC ROM */
void convert_objects(void);                     /* OLC ROM */
void convert_object(OBJ_INDEX_DATA *pObjIndex); /* OLC ROM */

#endif /* _ROM_DB_H_ */
