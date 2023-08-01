#ifndef _ROM_MERC_H_
#define _ROM_MERC_H_

#if defined(__cplusplus)
extern "C" {
#endif

/***************************************************************************
 *  Original Diku Mud copyright (C) 1990, 1991 by Sebastian Hammer,        *
 *  Michael Seifert, Hans Henrik St{rfeldt, Tom Madsen, and Katja Nyboe.   *
 *                                                                         *
 *  Merc Diku Mud improvments copyright (C) 1992, 1993 by Michael          *
 *  Chastain, Michael Quan, and Mitchell Tse.                              *
 *                                                                         *
 *  In order to use any part of this Merc Diku Mud, you must comply with   *
 *  both the original Diku license in 'license.doc' as well the Merc       *
 *  license in 'license.txt'.  In particular, you may not remove either of *
 *  these copyright notices.                                               *
 *                                                                         *
 *  Much time and thought has gone into this software and you are          *
 *  benefitting.  We hope that you share your changes too.  What goes      *
 *  around, comes around.                                                  *
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

#include <stdbool.h>
#include <stdio.h>
#include <time.h>

/*
 * Short scalar types.
 */
#if !defined(FALSE)
#define FALSE 0
#endif

#if !defined(TRUE)
#define TRUE 1
#endif

typedef short int sh_int;


/*
 * Structure types.
 */
typedef struct affect_data      AFFECT_DATA;
typedef struct area_data        AREA_DATA;
typedef struct ban_data         BAN_DATA;
typedef struct buf_type         BUFFER;
typedef struct char_data        CHAR_DATA;
typedef struct descriptor_data  DESCRIPTOR_DATA;
typedef struct exit_data        EXIT_DATA;
typedef struct extra_descr_data EXTRA_DESCR_DATA;
typedef struct help_data        HELP_DATA;
typedef struct kill_data        KILL_DATA;
typedef struct mem_data         MEM_DATA;
typedef struct mob_index_data   MOB_INDEX_DATA;
typedef struct note_data        NOTE_DATA;
typedef struct obj_data         OBJ_DATA;
typedef struct obj_index_data   OBJ_INDEX_DATA;
typedef struct pc_data          PC_DATA;
typedef struct gen_data         GEN_DATA;
typedef struct reset_data       RESET_DATA;
typedef struct room_index_data  ROOM_INDEX_DATA;
typedef struct shop_data        SHOP_DATA;
typedef struct time_info_data   TIME_INFO_DATA;
typedef struct weather_data     WEATHER_DATA;


/*
 * Function types.
 */
typedef void DO_FUN(CHAR_DATA *ch, char *argument);
typedef bool SPEC_FUN(CHAR_DATA *ch);
typedef void SPELL_FUN(int sn, int level, CHAR_DATA *ch, void *vo, int target);

#define DECLARE_DO_FUN(fun)    DO_FUN fun
#define DECLARE_SPEC_FUN(fun)  SPEC_FUN fun
#define DECLARE_SPELL_FUN(fun) SPELL_FUN fun


/*
 * String and memory management parameters.
 */
#define MAX_KEY_HASH       (1<<10)
#define MAX_STRING_LENGTH  4608
#define MAX_STRING_FMT_BUF 4800
#define MAX_INPUT_LENGTH   (1<<8)
#define PAGELEN            22


/*
 * Game parameters.
 * Increase the max'es if you add more of something.
 * Adjust the pulse numbers to suit yourself.
 */
#define MAX_SOCIALS        (1<<8)
#define MAX_SKILL          150
#define MAX_GROUP          30
#define MAX_IN_GROUP       15
#define MAX_ALIAS          5
#define MAX_CLASS          4
#define MAX_PC_RACE        5
#define MAX_CLAN           3
#define MAX_DAMAGE_MESSAGE 41
#define MAX_LEVEL          60
#define LEVEL_HERO         (MAX_LEVEL - 9)
#define LEVEL_IMMORTAL     (MAX_LEVEL - 8)

#define PULSE_PER_SECOND 4
#define PULSE_VIOLENCE   (3 * PULSE_PER_SECOND)
#define PULSE_MOBILE     (4 * PULSE_PER_SECOND)
#define PULSE_MUSIC      (6 * PULSE_PER_SECOND)
#define PULSE_TICK       (60 * PULSE_PER_SECOND)
#define PULSE_AREA       (120 * PULSE_PER_SECOND)

#define IMPLEMENTOR MAX_LEVEL
#define CREATOR     (MAX_LEVEL - 1)
#define SUPREME     (MAX_LEVEL - 2)
#define DEITY       (MAX_LEVEL - 3)
#define GOD         (MAX_LEVEL - 4)
#define IMMORTAL    (MAX_LEVEL - 5)
#define DEMI        (MAX_LEVEL - 6)
#define ANGEL       (MAX_LEVEL - 7)
#define AVATAR      (MAX_LEVEL - 8)
#define HERO        LEVEL_HERO


/*
 * Site ban structure.
 */

#define BAN_SUFFIX    1
#define BAN_PREFIX    2
#define BAN_NEWBIES   4
#define BAN_ALL       8
#define BAN_PERMIT    16
#define BAN_PERMANENT 32

struct ban_data {
    BAN_DATA *next;
    bool      valid;
    sh_int    ban_flags;
    sh_int    level;
    char     *name;
};

struct buf_type {
    BUFFER *next;
    bool    valid;
    sh_int  state;  /* error state of the buffer */
    sh_int  size;   /* size in k */
    char   *string; /* buffer's string */
};


/*
 * Time and weather stuff.
 */
#define SUN_DARK  0
#define SUN_RISE  1
#define SUN_LIGHT 2
#define SUN_SET   3

#define SKY_CLOUDLESS 0
#define SKY_CLOUDY    1
#define SKY_RAINING   2
#define SKY_LIGHTNING 3

struct time_info_data {
    int hour;
    int day;
    int month;
    int year;
};

struct weather_data {
    int mmhg;
    int change;
    int sky;
    int sunlight;
};


/*
 * Connected state for a channel.
 */
#define CON_PLAYING              0
#define CON_GET_NAME             1
#define CON_GET_OLD_PASSWORD     2
#define CON_CONFIRM_NEW_NAME     3
#define CON_GET_NEW_PASSWORD     4
#define CON_CONFIRM_NEW_PASSWORD 5
#define CON_GET_NEW_RACE         6
#define CON_GET_NEW_SEX          7
#define CON_GET_NEW_CLASS        8
#define CON_GET_ALIGNMENT        9
#define CON_DEFAULT_CHOICE       10
#define CON_GEN_GROUPS           11
#define CON_PICK_WEAPON          12
#define CON_READ_IMOTD           13
#define CON_READ_MOTD            14
#define CON_BREAK_CONNECT        15


/*
 * Descriptor (channel) structure.
 */
struct descriptor_data {
    DESCRIPTOR_DATA *next;
    DESCRIPTOR_DATA *snoop_by;
    CHAR_DATA       *character;
    CHAR_DATA       *original;
    bool             valid;
    char            *host;
    sh_int           descriptor;
    sh_int           connected;
    bool             fcommand;
    char             inbuf[4 * MAX_INPUT_LENGTH];
    char             incomm[MAX_INPUT_LENGTH];
    char             inlast[MAX_INPUT_LENGTH];
    int              repeat;
    char            *outbuf;
    int              outsize;
    int              outtop;
    char            *showstr_head;
    char            *showstr_point;
    void            *pEdit;   /* OLC */
    char           **pString; /* OLC */
    int              editor;  /* OLC */
};


/*
 * Attribute bonus structures.
 */
struct str_app_type {
    sh_int tohit;
    sh_int todam;
    sh_int carry;
    sh_int wield;
};

struct int_app_type {
    sh_int learn;
};

struct wis_app_type {
    sh_int practice;
};

struct dex_app_type {
    sh_int defensive;
};

struct con_app_type {
    sh_int hitp;
    sh_int shock;
};


/*
 * TO types for act.
 */
#define TO_ROOM    0
#define TO_NOTVICT 1
#define TO_VICT    2
#define TO_CHAR    3
#define TO_ALL     4


/*
 * Help table types.
 */
struct help_data {
    HELP_DATA *next;
    sh_int     level;
    char      *keyword;
    char      *text;
};


/*
 * Shop types.
 */
#define MAX_TRADE 5

struct shop_data {
    SHOP_DATA *next;                /* Next shop in list		*/
    sh_int     keeper;              /* Vnum of shop keeper mob	*/
    sh_int     buy_type[MAX_TRADE]; /* Item types shop will buy	*/
    sh_int     profit_buy;          /* Cost multiplier for buying	*/
    sh_int     profit_sell;         /* Cost multiplier for selling	*/
    sh_int     open_hour;           /* First opening hour		*/
    sh_int     close_hour;          /* First closing hour		*/
};


/*
 * Per-class stuff.
 */

#define MAX_GUILD 2
#define MAX_STATS 5
#define STAT_STR  0
#define STAT_INT  1
#define STAT_WIS  2
#define STAT_DEX  3
#define STAT_CON  4

struct class_type {
    char  *name;             /* the full name of the class */
    char   who_name[4];      /* Three-letter name for 'who'	*/
    sh_int attr_prime;       /* Prime attribute		*/
    sh_int weapon;           /* First weapon			*/
    sh_int guild[MAX_GUILD]; /* Vnum of guild rooms		*/
    sh_int skill_adept;      /* Maximum skill level		*/
    sh_int thac0_00;         /* Thac0 for level  0		*/
    sh_int thac0_32;         /* Thac0 for level 32		*/
    sh_int hp_min;           /* Min hp gained on leveling	*/
    sh_int hp_max;           /* Max hp gained on leveling	*/
    bool   fMana;            /* Class gains mana on level	*/
    char  *base_group;       /* base skills gained		*/
    char  *default_group;    /* default skills gained	*/
};

struct item_type {
    int   type;
    char *name;
};

struct weapon_type {
    char   *name;
    sh_int  vnum;
    sh_int  type;
    sh_int *gsn;
};

struct wiznet_type {
    char *name;
    long  flag;
    int   level;
};

struct attack_type {
    char *name;   /* name */
    char *noun;   /* message */
    int   damage; /* damage class */
};

struct race_type {
    char *name;    /* call name of the race */
    bool  pc_race; /* can be chosen by pcs */
    long  act;     /* act bits for the race */
    long  aff;     /* aff bits for the race */
    long  off;     /* off bits for the race */
    long  imm;     /* imm bits for the race */
    long  res;     /* res bits for the race */
    long  vuln;    /* vuln bits for the race */
    long  form;    /* default form flag for the race */
    long  parts;   /* default parts for the race */
};


struct pc_race_type /* additional data for pc races */
{
    char  *name; /* MUST be in race_type */
    char   who_name[6];
    sh_int points;                /* cost in points of the race */
    sh_int class_mult[MAX_CLASS]; /* exp multiplier for class, * 100 */
    char  *skills[5];             /* bonus skills for the race */
    sh_int stats[MAX_STATS];      /* starting stats */
    sh_int max_stats[MAX_STATS];  /* maximum stats */
    sh_int size;                  /* aff bits for the race */
};


struct spec_type {
    char     *name;     /* special function name */
    SPEC_FUN *function; /* the function */
};


/*
 * Data structure for notes.
 */

#define NOTE_NOTE    0
#define NOTE_IDEA    1
#define NOTE_PENALTY 2
#define NOTE_NEWS    3
#define NOTE_CHANGES 4
struct note_data {
    NOTE_DATA *next;
    bool       valid;
    sh_int     type;
    char      *sender;
    char      *date;
    char      *to_list;
    char      *subject;
    char      *text;
    time_t     date_stamp;
};


/*
 * An affect.
 */
struct affect_data {
    AFFECT_DATA *next;
    bool         valid;
    sh_int       where;
    sh_int       type;
    sh_int       level;
    sh_int       duration;
    sh_int       location;
    sh_int       modifier;
    int          bitvector;
};

/* where definitions */
#define TO_AFFECTS 0
#define TO_OBJECT  1
#define TO_IMMUNE  2
#define TO_RESIST  3
#define TO_VULN    4
#define TO_WEAPON  5


/*
 * A kill structure (indexed by level).
 */
struct kill_data {
    sh_int number;
    sh_int killed;
};


/***************************************************************************
 *                                                                         *
 *                   VALUES OF INTEREST TO AREA BUILDERS                   *
 *                   (Start of section ... start here)                     *
 *                                                                         *
 ***************************************************************************/

/*
 * Well known mob virtual numbers.
 * Defined in #MOBILES.
 */
#define MOB_VNUM_FIDO      3090
#define MOB_VNUM_CITYGUARD 3060
#define MOB_VNUM_VAMPIRE   3404

#define MOB_VNUM_PATROLMAN 2106
#define GROUP_VNUM_TROLLS  2100
#define GROUP_VNUM_OGRES   2101

/*
 * ACT bits for mobs.
 * Used in #MOBILES.
 */
#define ACT_IS_NPC        (1<<0) /* Auto set for mobs	*/
#define ACT_SENTINEL      (1<<1) /* Stays in one room	*/
#define ACT_SCAVENGER     (1<<2) /* Picks up objects	*/
#define ACT_AGGRESSIVE    (1<<5) /* Attacks PC's		*/
#define ACT_STAY_AREA     (1<<6) /* Won't leave area	*/
#define ACT_WIMPY         (1<<7)
#define ACT_PET           (1<<8) /* Auto set for pets	*/
#define ACT_TRAIN         (1<<9) /* Can train PC's	*/
#define ACT_PRACTICE      (1<<10) /* Can practice PC's	*/
#define ACT_UNDEAD        (1<<14)
#define ACT_CLERIC        (1<<16)
#define ACT_MAGE          (1<<17)
#define ACT_THIEF         (1<<18)
#define ACT_WARRIOR       (1<<19)
#define ACT_NOALIGN       (1<<20)
#define ACT_NOPURGE       (1<<21)
#define ACT_OUTDOORS      (1<<22)
#define ACT_INDOORS       (1<<24)
#define ACT_IS_HEALER     (1<<26)
#define ACT_GAIN          (1<<27)
#define ACT_UPDATE_ALWAYS (1<<28)
#define ACT_IS_CHANGER    (1<<29)

/* damage classes */
#define DAM_NONE      0
#define DAM_BASH      1
#define DAM_PIERCE    2
#define DAM_SLASH     3
#define DAM_FIRE      4
#define DAM_COLD      5
#define DAM_LIGHTNING 6
#define DAM_ACID      7
#define DAM_POISON    8
#define DAM_NEGATIVE  9
#define DAM_HOLY      10
#define DAM_ENERGY    11
#define DAM_MENTAL    12
#define DAM_DISEASE   13
#define DAM_DROWNING  14
#define DAM_LIGHT     15
#define DAM_OTHER     16
#define DAM_HARM      17
#define DAM_CHARM     18
#define DAM_SOUND     19

/* OFF bits for mobiles */
#define OFF_AREA_ATTACK (1<<0)
#define OFF_BACKSTAB    (1<<1)
#define OFF_BASH        (1<<2)
#define OFF_BERSERK     (1<<3)
#define OFF_DISARM      (1<<4)
#define OFF_DODGE       (1<<5)
#define OFF_FADE        (1<<6)
#define OFF_FAST        (1<<7)
#define OFF_KICK        (1<<8)
#define OFF_KICK_DIRT   (1<<9)
#define OFF_PARRY       (1<<10)
#define OFF_RESCUE      (1<<11)
#define OFF_TAIL        (1<<12)
#define OFF_TRIP        (1<<13)
#define OFF_CRUSH       (1<<14)
#define ASSIST_ALL      (1<<15)
#define ASSIST_ALIGN    (1<<16)
#define ASSIST_RACE     (1<<17)
#define ASSIST_PLAYERS  (1<<18)
#define ASSIST_GUARD    (1<<19)
#define ASSIST_VNUM     (1<<20)

/* return values for check_imm */
#define IS_NORMAL     0
#define IS_IMMUNE     1
#define IS_RESISTANT  2
#define IS_VULNERABLE 3

/* IMM bits for mobs */
#define IMM_SUMMON    (1)
#define IMM_CHARM     (2)
#define IMM_MAGIC     (4)
#define IMM_WEAPON    (8)
#define IMM_BASH      (16)
#define IMM_PIERCE    (32)
#define IMM_SLASH     (64)
#define IMM_FIRE      (1<<7)
#define IMM_COLD      (1<<8)
#define IMM_LIGHTNING (1<<9)
#define IMM_ACID      (1<<10)
#define IMM_POISON    (1<<11)
#define IMM_NEGATIVE  (1<<12)
#define IMM_HOLY      (1<<13)
#define IMM_ENERGY    (1<<14)
#define IMM_MENTAL    (1<<15)
#define IMM_DISEASE   (1<<16)
#define IMM_DROWNING  (1<<17)
#define IMM_LIGHT     (1<<18)
#define IMM_SOUND     (1<<19)
#define IMM_WOOD      (1<<23)
#define IMM_SILVER    (1<<24)
#define IMM_IRON      (1<<25)

/* RES bits for mobs */
#define RES_SUMMON    (1)
#define RES_CHARM     (2)
#define RES_MAGIC     (4)
#define RES_WEAPON    (8)
#define RES_BASH      (16)
#define RES_PIERCE    (32)
#define RES_SLASH     (64)
#define RES_FIRE      (1<<7)
#define RES_COLD      (1<<8)
#define RES_LIGHTNING (1<<9)
#define RES_ACID      (1<<10)
#define RES_POISON    (1<<11)
#define RES_NEGATIVE  (1<<12)
#define RES_HOLY      (1<<13)
#define RES_ENERGY    (1<<14)
#define RES_MENTAL    (1<<15)
#define RES_DISEASE   (1<<16)
#define RES_DROWNING  (1<<17)
#define RES_LIGHT     (1<<18)
#define RES_SOUND     (1<<19)
#define RES_WOOD      (1<<23)
#define RES_SILVER    (1<<24)
#define RES_IRON      (1<<25)

/* VULN bits for mobs */
#define VULN_SUMMON    (1)
#define VULN_CHARM     (2)
#define VULN_MAGIC     (4)
#define VULN_WEAPON    (8)
#define VULN_BASH      (16)
#define VULN_PIERCE    (32)
#define VULN_SLASH     (64)
#define VULN_FIRE      (1<<7)
#define VULN_COLD      (1<<8)
#define VULN_LIGHTNING (1<<9)
#define VULN_ACID      (1<<10)
#define VULN_POISON    (1<<11)
#define VULN_NEGATIVE  (1<<12)
#define VULN_HOLY      (1<<13)
#define VULN_ENERGY    (1<<14)
#define VULN_MENTAL    (1<<15)
#define VULN_DISEASE   (1<<16)
#define VULN_DROWNING  (1<<17)
#define VULN_LIGHT     (1<<18)
#define VULN_SOUND     (1<<19)
#define VULN_WOOD      (1<<23)
#define VULN_SILVER    (1<<24)
#define VULN_IRON      (1<<25)

/* body form */
#define FORM_EDIBLE        (1)
#define FORM_POISON        (2)
#define FORM_MAGICAL       (4)
#define FORM_INSTANT_DECAY (8)
#define FORM_OTHER         (1<<4) /* defined by material bit */

/* actual form */
#define FORM_ANIMAL     (64)
#define FORM_SENTIENT   (1<<7)
#define FORM_UNDEAD     (1<<8)
#define FORM_CONSTRUCT  (1<<9)
#define FORM_MIST       (1<<10)
#define FORM_INTANGIBLE (1<<11)

#define FORM_BIPED      (1<<12)
#define FORM_CENTAUR    (1<<13)
#define FORM_INSECT     (1<<14)
#define FORM_SPIDER     (1<<15)
#define FORM_CRUSTACEAN (1<<16)
#define FORM_WORM       (1<<17)
#define FORM_BLOB       (1<<18)

#define FORM_MAMMAL     (1<<21)
#define FORM_BIRD       (1<<22)
#define FORM_REPTILE    (1<<23)
#define FORM_SNAKE      (1<<24)
#define FORM_DRAGON     (1<<25)
#define FORM_AMPHIBIAN  (1<<26)
#define FORM_FISH       (1<<27)
#define FORM_COLD_BLOOD (1<<28)

/* body parts */
#define PART_HEAD        (1)
#define PART_ARMS        (2)
#define PART_LEGS        (4)
#define PART_HEART       (8)
#define PART_BRAINS      (16)
#define PART_GUTS        (32)
#define PART_HANDS       (64)
#define PART_FEET        (1<<7)
#define PART_FINGERS     (1<<8)
#define PART_EAR         (1<<9)
#define PART_EYE         (1<<10)
#define PART_LONG_TONGUE (1<<11)
#define PART_EYESTALKS   (1<<12)
#define PART_TENTACLES   (1<<13)
#define PART_FINS        (1<<14)
#define PART_WINGS       (1<<15)
#define PART_TAIL        (1<<16)
/* for combat */
#define PART_CLAWS  (1<<20)
#define PART_FANGS  (1<<21)
#define PART_HORNS  (1<<22)
#define PART_SCALES (1<<23)
#define PART_TUSKS  (1<<24)


/*
 * Bits for 'affected_by'.
 * Used in #MOBILES.
 */
#define AFF_BLIND         (1)
#define AFF_INVISIBLE     (2)
#define AFF_DETECT_EVIL   (4)
#define AFF_DETECT_INVIS  (8)
#define AFF_DETECT_MAGIC  (16)
#define AFF_DETECT_HIDDEN (32)
#define AFF_DETECT_GOOD   (64)
#define AFF_SANCTUARY     (1<<7)
#define AFF_FAERIE_FIRE   (1<<8)
#define AFF_INFRARED      (1<<9)
#define AFF_CURSE         (1<<10)
#define AFF_UNUSED_FLAG   (1<<11) /* unused */
#define AFF_POISON        (1<<12)
#define AFF_PROTECT_EVIL  (1<<13)
#define AFF_PROTECT_GOOD  (1<<14)
#define AFF_SNEAK         (1<<15)
#define AFF_HIDE          (1<<16)
#define AFF_SLEEP         (1<<17)
#define AFF_CHARM         (1<<18)
#define AFF_FLYING        (1<<19)
#define AFF_PASS_DOOR     (1<<20)
#define AFF_HASTE         (1<<21)
#define AFF_CALM          (1<<22)
#define AFF_PLAGUE        (1<<23)
#define AFF_WEAKEN        (1<<24)
#define AFF_DARK_VISION   (1<<25)
#define AFF_BERSERK       (1<<26)
#define AFF_SWIM          (1<<27)
#define AFF_REGENERATION  (1<<28)
#define AFF_SLOW          (1<<29)


/*
 * Sex.
 * Used in #MOBILES.
 */
#define SEX_NEUTRAL 0
#define SEX_MALE    1
#define SEX_FEMALE  2

/* AC types */
#define AC_PIERCE 0
#define AC_BASH   1
#define AC_SLASH  2
#define AC_EXOTIC 3

/* dice */
#define DICE_NUMBER 0
#define DICE_TYPE   1
#define DICE_BONUS  2

/* size */
#define SIZE_TINY   0
#define SIZE_SMALL  1
#define SIZE_MEDIUM 2
#define SIZE_LARGE  3
#define SIZE_HUGE   4
#define SIZE_GIANT  5


/*
 * Well known object virtual numbers.
 * Defined in #OBJECTS.
 */
#define OBJ_VNUM_SILVER_ONE  1
#define OBJ_VNUM_GOLD_ONE    2
#define OBJ_VNUM_GOLD_SOME   3
#define OBJ_VNUM_SILVER_SOME 4
#define OBJ_VNUM_COINS       5

#define OBJ_VNUM_CORPSE_NPC   10
#define OBJ_VNUM_CORPSE_PC    11
#define OBJ_VNUM_SEVERED_HEAD 12
#define OBJ_VNUM_TORN_HEART   13
#define OBJ_VNUM_SLICED_ARM   14
#define OBJ_VNUM_SLICED_LEG   15
#define OBJ_VNUM_GUTS         16
#define OBJ_VNUM_BRAINS       17

#define OBJ_VNUM_MUSHROOM   20
#define OBJ_VNUM_LIGHT_BALL 21
#define OBJ_VNUM_SPRING     22
#define OBJ_VNUM_DISC       23
#define OBJ_VNUM_PORTAL     25

#define OBJ_VNUM_ROSE 1001

#define OBJ_VNUM_PIT 3010

#define OBJ_VNUM_SCHOOL_MACE    3700
#define OBJ_VNUM_SCHOOL_DAGGER  3701
#define OBJ_VNUM_SCHOOL_SWORD   3702
#define OBJ_VNUM_SCHOOL_SPEAR   3717
#define OBJ_VNUM_SCHOOL_STAFF   3718
#define OBJ_VNUM_SCHOOL_AXE     3719
#define OBJ_VNUM_SCHOOL_FLAIL   3720
#define OBJ_VNUM_SCHOOL_WHIP    3721
#define OBJ_VNUM_SCHOOL_POLEARM 3722

#define OBJ_VNUM_SCHOOL_VEST   3703
#define OBJ_VNUM_SCHOOL_SHIELD 3704
#define OBJ_VNUM_SCHOOL_BANNER 3716
#define OBJ_VNUM_MAP           3162

#define OBJ_VNUM_WHISTLE 2116


/*
 * Item types.
 * Used in #OBJECTS.
 */
#define ITEM_LIGHT      1
#define ITEM_SCROLL     2
#define ITEM_WAND       3
#define ITEM_STAFF      4
#define ITEM_WEAPON     5
#define ITEM_TREASURE   8
#define ITEM_ARMOR      9
#define ITEM_POTION     10
#define ITEM_CLOTHING   11
#define ITEM_FURNITURE  12
#define ITEM_TRASH      13
#define ITEM_CONTAINER  15
#define ITEM_DRINK_CON  17
#define ITEM_KEY        18
#define ITEM_FOOD       19
#define ITEM_MONEY      20
#define ITEM_BOAT       22
#define ITEM_CORPSE_NPC 23
#define ITEM_CORPSE_PC  24
#define ITEM_FOUNTAIN   25
#define ITEM_PILL       26
#define ITEM_PROTECT    27
#define ITEM_MAP        28
#define ITEM_PORTAL     29
#define ITEM_WARP_STONE 30
#define ITEM_ROOM_KEY   31
#define ITEM_GEM        32
#define ITEM_JEWELRY    33
#define ITEM_JUKEBOX    34

/*
 * Material types
 */
#define MAT_STEEL       1
#define MAT_STONE       2
#define MAT_BRASS       3
#define MAT_BONE        4
#define MAT_ENERGY      5
#define MAT_MITHRIL     6
#define MAT_COPPER      7
#define MAT_SILK        8
#define MAT_MARBLE      9
#define MAT_GLASS       10
#define MAT_WATER       11
#define MAT_FLESH       12
#define MAT_PLATINUM    13
#define MAT_GRANITE     14
#define MAT_LEATHER     15
#define MAT_CLOTH       16
#define MAT_GEMSTONE    17
#define MAT_GOLD        18
#define MAT_PORCELAIN   19
#define MAT_OBSIDIAN    20
#define MAT_DRAGONSCALE 21
#define MAT_EBONY       22
#define MAT_BRONZE      23
#define MAT_WOOD        24
#define MAT_SILVER      25
#define MAT_IRON        26
#define MAT_BLOODSTONE  27
#define MAT_FOOD        28
#define MAT_LEAD        29
#define MAT_WAX         30

/*
 * Extra flags.
 * Used in #OBJECTS.
 */
#define ITEM_GLOW         (1)
#define ITEM_HUM          (2)
#define ITEM_DARK         (4)
#define ITEM_LOCK         (8)
#define ITEM_EVIL         (16)
#define ITEM_INVIS        (32)
#define ITEM_MAGIC        (64)
#define ITEM_NODROP       (1<<7)
#define ITEM_BLESS        (1<<8)
#define ITEM_ANTI_GOOD    (1<<9)
#define ITEM_ANTI_EVIL    (1<<10)
#define ITEM_ANTI_NEUTRAL (1<<11)
#define ITEM_NOREMOVE     (1<<12)
#define ITEM_INVENTORY    (1<<13)
#define ITEM_NOPURGE      (1<<14)
#define ITEM_ROT_DEATH    (1<<15)
#define ITEM_VIS_DEATH    (1<<16)
#define ITEM_NONMETAL     (1<<18)
#define ITEM_NOLOCATE     (1<<19)
#define ITEM_MELT_DROP    (1<<20)
#define ITEM_HAD_TIMER    (1<<21)
#define ITEM_SELL_EXTRACT (1<<22)
#define ITEM_BURN_PROOF   (1<<24)
#define ITEM_NOUNCURSE    (1<<25)


/*
 * Wear flags.
 * Used in #OBJECTS.
 */
#define ITEM_TAKE        (1)
#define ITEM_WEAR_FINGER (2)
#define ITEM_WEAR_NECK   (4)
#define ITEM_WEAR_BODY   (8)
#define ITEM_WEAR_HEAD   (16)
#define ITEM_WEAR_LEGS   (32)
#define ITEM_WEAR_FEET   (64)
#define ITEM_WEAR_HANDS  (1<<7)
#define ITEM_WEAR_ARMS   (1<<8)
#define ITEM_WEAR_SHIELD (1<<9)
#define ITEM_WEAR_ABOUT  (1<<10)
#define ITEM_WEAR_WAIST  (1<<11)
#define ITEM_WEAR_WRIST  (1<<12)
#define ITEM_WIELD       (1<<13)
#define ITEM_HOLD        (1<<14)
#define ITEM_NO_SAC      (1<<15)
#define ITEM_WEAR_FLOAT  (1<<16)

/* weapon class */
#define WEAPON_EXOTIC  0
#define WEAPON_SWORD   1
#define WEAPON_DAGGER  2
#define WEAPON_SPEAR   3
#define WEAPON_MACE    4
#define WEAPON_AXE     5
#define WEAPON_FLAIL   6
#define WEAPON_WHIP    7
#define WEAPON_POLEARM 8

/* weapon types */
#define WEAPON_FLAMING   (1)
#define WEAPON_FROST     (2)
#define WEAPON_VAMPIRIC  (4)
#define WEAPON_SHARP     (8)
#define WEAPON_VORPAL    (16)
#define WEAPON_TWO_HANDS (32)
#define WEAPON_SHOCKING  (64)
#define WEAPON_POISON    (1<<7)

/* gate flags */
#define GATE_NORMAL_EXIT (1)
#define GATE_NOCURSE     (2)
#define GATE_GOWITH      (4)
#define GATE_BUGGY       (8)
#define GATE_RANDOM      (16)

/* furniture flags */
#define STAND_AT   (1)
#define STAND_ON   (2)
#define STAND_IN   (4)
#define SIT_AT     (8)
#define SIT_ON     (16)
#define SIT_IN     (32)
#define REST_AT    (64)
#define REST_ON    (1<<7)
#define REST_IN    (1<<8)
#define SLEEP_AT   (1<<9)
#define SLEEP_ON   (1<<10)
#define SLEEP_IN   (1<<11)
#define PUT_AT     (1<<12)
#define PUT_ON     (1<<13)
#define PUT_IN     (1<<14)
#define PUT_INSIDE (1<<15)


/*
 * Apply types (for affects).
 * Used in #OBJECTS.
 */
#define APPLY_NONE          0
#define APPLY_STR           1
#define APPLY_DEX           2
#define APPLY_INT           3
#define APPLY_WIS           4
#define APPLY_CON           5
#define APPLY_SEX           6
#define APPLY_CLASS         7
#define APPLY_LEVEL         8
#define APPLY_AGE           9
#define APPLY_HEIGHT        10
#define APPLY_WEIGHT        11
#define APPLY_MANA          12
#define APPLY_HIT           13
#define APPLY_MOVE          14
#define APPLY_GOLD          15
#define APPLY_EXP           16
#define APPLY_AC            17
#define APPLY_HITROLL       18
#define APPLY_DAMROLL       19
#define APPLY_SAVES         20
#define APPLY_SAVING_PARA   20
#define APPLY_SAVING_ROD    21
#define APPLY_SAVING_PETRI  22
#define APPLY_SAVING_BREATH 23
#define APPLY_SAVING_SPELL  24
#define APPLY_SPELL_AFFECT  25

/*
 * Values for containers (value[1]).
 * Used in #OBJECTS.
 */
#define CONT_CLOSEABLE 1
#define CONT_PICKPROOF 2
#define CONT_CLOSED    4
#define CONT_LOCKED    8
#define CONT_PUT_ON    16


/*
 * Well known room virtual numbers.
 * Defined in #ROOMS.
 */
#define ROOM_VNUM_LIMBO   2
#define ROOM_VNUM_CHAT    1200
#define ROOM_VNUM_TEMPLE  3001
#define ROOM_VNUM_ALTAR   3054
#define ROOM_VNUM_SCHOOL  3700
#define ROOM_VNUM_BALANCE 4500
#define ROOM_VNUM_CIRCLE  4400
#define ROOM_VNUM_DEMISE  4201
#define ROOM_VNUM_HONOR   4300


/*
 * Room flags.
 * Used in #ROOMS.
 */
#define ROOM_DARK    (1)
#define ROOM_NO_MOB  (4)
#define ROOM_INDOORS (8)

#define ROOM_PRIVATE      (1<<9)
#define ROOM_SAFE         (1<<10)
#define ROOM_SOLITARY     (1<<11)
#define ROOM_PET_SHOP     (1<<12)
#define ROOM_NO_RECALL    (1<<13)
#define ROOM_IMP_ONLY     (1<<14)
#define ROOM_GODS_ONLY    (1<<15)
#define ROOM_HEROES_ONLY  (1<<16)
#define ROOM_NEWBIES_ONLY (1<<17)
#define ROOM_LAW          (1<<18)
#define ROOM_NOWHERE      (1<<19)


/*
 * Directions.
 * Used in #ROOMS.
 */
#define DIR_NORTH 0
#define DIR_EAST  1
#define DIR_SOUTH 2
#define DIR_WEST  3
#define DIR_UP    4
#define DIR_DOWN  5


/*
 * Exit flags.
 * Used in #ROOMS.
 */
#define EX_ISDOOR      (1)
#define EX_CLOSED      (2)
#define EX_LOCKED      (4)
#define EX_PICKPROOF   (32)
#define EX_NOPASS      (64)
#define EX_EASY        (1<<7)
#define EX_HARD        (1<<8)
#define EX_INFURIATING (1<<9)
#define EX_NOCLOSE     (1<<10)
#define EX_NOLOCK      (1<<11)


/*
 * Sector types.
 * Used in #ROOMS.
 */
#define SECT_INSIDE       0
#define SECT_CITY         1
#define SECT_FIELD        2
#define SECT_FOREST       3
#define SECT_HILLS        4
#define SECT_MOUNTAIN     5
#define SECT_WATER_SWIM   6
#define SECT_WATER_NOSWIM 7
#define SECT_UNUSED       8
#define SECT_AIR          9
#define SECT_DESERT       10
#define SECT_MAX          11


/*
 * Equpiment wear locations.
 * Used in #RESETS.
 */
#define WEAR_NONE     (-1)
#define WEAR_LIGHT    0
#define WEAR_FINGER_L 1
#define WEAR_FINGER_R 2
#define WEAR_NECK_1   3
#define WEAR_NECK_2   4
#define WEAR_BODY     5
#define WEAR_HEAD     6
#define WEAR_LEGS     7
#define WEAR_FEET     8
#define WEAR_HANDS    9
#define WEAR_ARMS     10
#define WEAR_SHIELD   11
#define WEAR_ABOUT    12
#define WEAR_WAIST    13
#define WEAR_WRIST_L  14
#define WEAR_WRIST_R  15
#define WEAR_WIELD    16
#define WEAR_HOLD     17
#define WEAR_FLOAT    18
#define MAX_WEAR      19


/***************************************************************************
 *                                                                         *
 *                   VALUES OF INTEREST TO AREA BUILDERS                   *
 *                   (End of this section ... stop here)                   *
 *                                                                         *
 ***************************************************************************/

/*
 * Conditions.
 */
#define COND_DRUNK  0
#define COND_FULL   1
#define COND_THIRST 2
#define COND_HUNGER 3


/*
 * Positions.
 */
#define POS_DEAD     0
#define POS_MORTAL   1
#define POS_INCAP    2
#define POS_STUNNED  3
#define POS_SLEEPING 4
#define POS_RESTING  5
#define POS_SITTING  6
#define POS_FIGHTING 7
#define POS_STANDING 8


/*
 * ACT bits for players.
 */
#define PLR_IS_NPC (1) /* Don't EVER set.	*/

/* RT auto flags */
#define PLR_AUTOASSIST (4)
#define PLR_AUTOEXIT   (8)
#define PLR_AUTOLOOT   (16)
#define PLR_AUTOSAC    (32)
#define PLR_AUTOGOLD   (64)
#define PLR_AUTOSPLIT  (1<<7)

/* RT personal flags */
#define PLR_HOLYLIGHT (1<<13)
#define PLR_CANLOOT   (1<<15)
#define PLR_NOSUMMON  (1<<16)
#define PLR_NOFOLLOW  (1<<17)
/* 2 bits reserved, S-T */

/* penalty flags */
#define PLR_PERMIT (1<<20)
#define PLR_LOG    (1<<22)
#define PLR_DENY   (1<<23)
#define PLR_FREEZE (1<<24)
#define PLR_THIEF  (1<<25)
#define PLR_KILLER (1<<26)


/* RT comm flags -- may be used on both mobs and chars */
#define COMM_QUIET      (1)
#define COMM_DEAF       (2)
#define COMM_NOWIZ      (4)
#define COMM_NOAUCTION  (8)
#define COMM_NOGOSSIP   (16)
#define COMM_NOQUESTION (32)
#define COMM_NOMUSIC    (64)
#define COMM_NOCLAN     (1<<7)
#define COMM_NOQUOTE    (1<<8)
#define COMM_SHOUTSOFF  (1<<9)

/* display flags */
#define COMM_COMPACT      (1<<11)
#define COMM_BRIEF        (1<<12)
#define COMM_PROMPT       (1<<13)
#define COMM_COMBINE      (1<<14)
#define COMM_TELNET_GA    (1<<15)
#define COMM_SHOW_AFFECTS (1<<16)
#define COMM_NOGRATS      (1<<17)

/* penalties */
#define COMM_NOEMOTE     (1<<19)
#define COMM_NOSHOUT     (1<<20)
#define COMM_NOTELL      (1<<21)
#define COMM_NOCHANNELS  (1<<22)
#define COMM_SNOOP_PROOF (1<<24)
#define COMM_AFK         (1<<25)

/* WIZnet flags */
#define WIZ_ON        (1)
#define WIZ_TICKS     (2)
#define WIZ_LOGINS    (4)
#define WIZ_SITES     (8)
#define WIZ_LINKS     (16)
#define WIZ_DEATHS    (32)
#define WIZ_RESETS    (64)
#define WIZ_MOBDEATHS (1<<7)
#define WIZ_FLAGS     (1<<8)
#define WIZ_PENALTIES (1<<9)
#define WIZ_SACCING   (1<<10)
#define WIZ_LEVELS    (1<<11)
#define WIZ_SECURE    (1<<12)
#define WIZ_SWITCHES  (1<<13)
#define WIZ_SNOOPS    (1<<14)
#define WIZ_RESTORE   (1<<15)
#define WIZ_LOAD      (1<<16)
#define WIZ_NEWBIE    (1<<17)
#define WIZ_PREFIX    (1<<18)
#define WIZ_SPAM      (1<<19)

/*
 * Prototype for a mob.
 * This is the in-memory version of #MOBILES.
 */
struct mob_index_data {
    AREA_DATA      *area; /* OLC */
    MOB_INDEX_DATA *next;
    SPEC_FUN       *spec_fun;
    SHOP_DATA      *pShop;
    sh_int          vnum;
    sh_int          group;
    bool            new_format;
    sh_int          count;
    sh_int          killed;
    char           *player_name;
    char           *short_descr;
    char           *long_descr;
    char           *description;
    long            act;
    long            affected_by;
    sh_int          alignment;
    sh_int          level;
    sh_int          hitroll;
    sh_int          hit[3];
    sh_int          mana[3];
    sh_int          damage[3];
    sh_int          ac[4];
    sh_int          dam_type;
    long            off_flags;
    long            imm_flags;
    long            res_flags;
    long            vuln_flags;
    sh_int          start_pos;
    sh_int          default_pos;
    sh_int          sex;
    sh_int          race;
    long            wealth;
    long            form;
    long            parts;
    sh_int          size;
    char           *material;
};


/* memory settings */
#define MEM_CUSTOMER 1
#define MEM_SELLER   2
#define MEM_HOSTILE  4
#define MEM_AFRAID   8

/* memory for mobs */
struct mem_data {
    MEM_DATA *next;
    bool      valid;
    int       id;
    int       reaction;
    time_t    when;
};


/*
 * One character (PC or NPC).
 */
struct char_data {
    CHAR_DATA       *next;
    CHAR_DATA       *next_in_room;
    CHAR_DATA       *master;
    CHAR_DATA       *leader;
    CHAR_DATA       *fighting;
    CHAR_DATA       *reply;
    CHAR_DATA       *pet;
    MEM_DATA        *memory;
    SPEC_FUN        *spec_fun;
    MOB_INDEX_DATA  *pIndexData;
    DESCRIPTOR_DATA *desc;
    AFFECT_DATA     *affected;
    NOTE_DATA       *pnote;
    OBJ_DATA        *carrying;
    OBJ_DATA        *on;
    ROOM_INDEX_DATA *in_room;
    ROOM_INDEX_DATA *was_in_room;
    AREA_DATA       *zone;
    PC_DATA         *pcdata;
    GEN_DATA        *gen_data;
    bool             valid;
    char            *name;
    long             id;
    sh_int           version;
    char            *short_descr;
    char            *long_descr;
    char            *description;
    char            *prompt;
    char            *prefix;
    sh_int           group;
    sh_int           clan;
    sh_int           sex;
    sh_int class;
    sh_int race;
    sh_int level;
    sh_int trust;
    int    played;
    int    lines; /* for the pager */
    time_t logon;
    sh_int timer;
    sh_int wait;
    sh_int daze;
    sh_int hit;
    sh_int max_hit;
    sh_int mana;
    sh_int max_mana;
    sh_int move;
    sh_int max_move;
    long   gold;
    long   silver;
    int    exp;
    long   act;
    long   comm;   /* RT added to pad the vector */
    long   wiznet; /* wiz stuff */
    long   imm_flags;
    long   res_flags;
    long   vuln_flags;
    sh_int invis_level;
    sh_int incog_level;
    long   affected_by;
    sh_int position;
    sh_int practice;
    sh_int train;
    sh_int carry_weight;
    sh_int carry_number;
    sh_int saving_throw;
    sh_int alignment;
    sh_int hitroll;
    sh_int damroll;
    sh_int armor[4];
    sh_int wimpy;
    /* stats */
    sh_int perm_stat[MAX_STATS];
    sh_int mod_stat[MAX_STATS];
    /* parts stuff */
    long   form;
    long   parts;
    sh_int size;
    char  *material;
    /* mobile stuff */
    long   off_flags;
    sh_int damage[3];
    sh_int dam_type;
    sh_int start_pos;
    sh_int default_pos;
};


/*
 * Data which only PC's have.
 */
struct pc_data {
    int      security; /* OLC */ /* Builder security */
    PC_DATA *next;
    BUFFER  *buffer;
    bool     valid;
    char    *pwd;
    char    *bamfin;
    char    *bamfout;
    char    *title;
    time_t   last_note;
    time_t   last_idea;
    time_t   last_penalty;
    time_t   last_news;
    time_t   last_changes;
    sh_int   perm_hit;
    sh_int   perm_mana;
    sh_int   perm_move;
    sh_int   true_sex;
    int      last_level;
    sh_int   condition[4];
    sh_int   learned[MAX_SKILL];
    bool     group_known[MAX_GROUP];
    sh_int   points;
    bool     confirm_delete;
    char    *alias[MAX_ALIAS];
    char    *alias_sub[MAX_ALIAS];
};

/* Data for generating characters -- only used during generation */
struct gen_data {
    GEN_DATA *next;
    bool      valid;
    bool      skill_chosen[MAX_SKILL];
    bool      group_chosen[MAX_GROUP];
    int       points_chosen;
};


/*
 * Liquids.
 */
#define LIQ_WATER 0

struct liq_type {
    char  *liq_name;
    char  *liq_color;
    sh_int liq_affect[5];
};


/*
 * Extra description data for a room or object.
 */
struct extra_descr_data {
    EXTRA_DESCR_DATA *next; /* Next in list                     */
    bool              valid;
    char             *keyword;     /* Keyword in look/examine          */
    char             *description; /* What to see                      */
};


/*
 * Prototype for an object.
 */
struct obj_index_data {
    AREA_DATA        *area; /* OLC */
    OBJ_INDEX_DATA   *next;
    EXTRA_DESCR_DATA *extra_descr;
    AFFECT_DATA      *affected;
    bool              new_format;
    char             *name;
    char             *short_descr;
    char             *description;
    sh_int            vnum;
    sh_int            reset_num;
    char             *material;
    sh_int            item_type;
    int               extra_flags;
    int               wear_flags;
    sh_int            level;
    sh_int            condition;
    sh_int            count;
    sh_int            weight;
    int               cost;
    int               value[5];
};


/*
 * One object.
 */
struct obj_data {
    OBJ_DATA         *next;
    OBJ_DATA         *next_content;
    OBJ_DATA         *contains;
    OBJ_DATA         *in_obj;
    OBJ_DATA         *on;
    CHAR_DATA        *carried_by;
    EXTRA_DESCR_DATA *extra_descr;
    AFFECT_DATA      *affected;
    OBJ_INDEX_DATA   *pIndexData;
    ROOM_INDEX_DATA  *in_room;
    bool              valid;
    bool              enchanted;
    char             *owner;
    char             *name;
    char             *short_descr;
    char             *description;
    sh_int            item_type;
    int               extra_flags;
    int               wear_flags;
    sh_int            wear_loc;
    sh_int            weight;
    int               cost;
    sh_int            level;
    sh_int            condition;
    char             *material;
    sh_int            timer;
    int               value[5];
};


/*
 * Exit data.
 */
struct exit_data {
    EXIT_DATA *next;      /* OLC */
    int        rs_flags;  /* OLC */
    int        orig_door; /* OLC */

    union {
        ROOM_INDEX_DATA *to_room;
        sh_int           vnum;
    } u1;
    sh_int exit_info;
    sh_int key;
    char  *keyword;
    char  *description;
};


/*
 * Reset commands:
 *   '*': comment
 *   'M': read a mobile
 *   'O': read an object
 *   'P': put object in object
 *   'G': give object to mobile
 *   'E': equip object to mobile
 *   'D': set state of door
 *   'R': randomize room exits
 *   'S': stop (end of list)
 */

/*
 * Area-reset definition.
 */
struct reset_data {
    RESET_DATA *next;
    char        command;
    sh_int      arg1;
    sh_int      arg2;
    sh_int      arg3;
    sh_int      arg4;
};


/* New area_data for OLC */
struct area_data {
    AREA_DATA *next; /*
RESET_DATA *	reset_first;     *  Removed for OLC reset system.
RESET_DATA *	reset_last;	 */
    char *name;
    char *credits;
    int   age;
    int   nplayer;
    bool  empty;              /* ROM OLC */
    char *filename;           /* OLC */
    char *builders; /* OLC */ /* Listing of */
    int   security; /* OLC */ /* Value 1-9  */
    int   lvnum; /* OLC */    /* Lower vnum */
    int   uvnum; /* OLC */    /* Upper vnum */
    int   vnum; /* OLC */     /* Area vnum  */
    int   area_flags;         /* OLC */
};

/*
 * Room type.
 */
struct room_index_data {
    RESET_DATA       *reset_first; /* OLC */
    RESET_DATA       *reset_last;  /* OLC */
    ROOM_INDEX_DATA  *next;
    CHAR_DATA        *people;
    OBJ_DATA         *contents;
    EXTRA_DESCR_DATA *extra_descr;
    AREA_DATA        *area;
    EXIT_DATA        *exit[6];
    EXIT_DATA        *old_exit[6];
    char             *name;
    char             *description;
    char             *owner;
    sh_int            vnum;
    int               room_flags;
    sh_int            light;
    sh_int            sector_type;
    sh_int            heal_rate;
    sh_int            mana_rate;
    sh_int            clan;
};


/*
 * Types of attacks.
 * Must be non-overlapping with spell/skill types,
 * but may be arbitrary beyond that.
 */
#define TYPE_UNDEFINED (-1)
#define TYPE_HIT       1000


/*
 *  Target types.
 */
#define TAR_IGNORE         0
#define TAR_CHAR_OFFENSIVE 1
#define TAR_CHAR_DEFENSIVE 2
#define TAR_CHAR_SELF      3
#define TAR_OBJ_INV        4
#define TAR_OBJ_CHAR_DEF   5
#define TAR_OBJ_CHAR_OFF   6

#define TARGET_CHAR 0
#define TARGET_OBJ  1
#define TARGET_ROOM 2
#define TARGET_NONE 3


/*
 * Skills include spells as a particular case.
 */
struct skill_type {
    char      *name;                   /* Name of skill		*/
    sh_int     skill_level[MAX_CLASS]; /* Level needed by class	*/
    sh_int     rating[MAX_CLASS];      /* How hard it is to learn	*/
    SPELL_FUN *spell_fun;              /* Spell pointer (for spells)	*/
    sh_int     target;                 /* Legal targets		*/
    sh_int     minimum_position;       /* Position for caster / user	*/
    sh_int    *pgsn;                   /* Pointer to associated gsn	*/
    sh_int     slot;                   /* Slot for #OBJECT loading	*/
    sh_int     min_mana;               /* Minimum mana used		*/
    sh_int     beats;                  /* Waiting time after use	*/
    char      *noun_damage;            /* Damage message		*/
    char      *msg_off;                /* Wear off message		*/
    char      *msg_obj;                /* Wear off message for obects	*/
};

struct group_type {
    char  *name;
    sh_int rating[MAX_CLASS];
    char  *spells[MAX_IN_GROUP];
};


/*
 * These are skill_lookup return values for common skills and spells.
 */
extern sh_int gsn_backstab;
extern sh_int gsn_dodge;
extern sh_int gsn_envenom;
extern sh_int gsn_hide;
extern sh_int gsn_peek;
extern sh_int gsn_pick_lock;
extern sh_int gsn_sneak;
extern sh_int gsn_steal;

extern sh_int gsn_disarm;
extern sh_int gsn_enhanced_damage;
extern sh_int gsn_kick;
extern sh_int gsn_parry;
extern sh_int gsn_rescue;
extern sh_int gsn_second_attack;
extern sh_int gsn_third_attack;

extern sh_int gsn_blindness;
extern sh_int gsn_charm_person;
extern sh_int gsn_curse;
extern sh_int gsn_invis;
extern sh_int gsn_mass_invis;
extern sh_int gsn_plague;
extern sh_int gsn_poison;
extern sh_int gsn_sleep;
extern sh_int gsn_fly;
extern sh_int gsn_sanctuary;

/* new gsns */
extern sh_int gsn_axe;
extern sh_int gsn_dagger;
extern sh_int gsn_flail;
extern sh_int gsn_mace;
extern sh_int gsn_polearm;
extern sh_int gsn_shield_block;
extern sh_int gsn_spear;
extern sh_int gsn_sword;
extern sh_int gsn_whip;

extern sh_int gsn_bash;
extern sh_int gsn_berserk;
extern sh_int gsn_dirt;
extern sh_int gsn_hand_to_hand;
extern sh_int gsn_trip;

extern sh_int gsn_fast_healing;
extern sh_int gsn_haggle;
extern sh_int gsn_lore;
extern sh_int gsn_meditation;

extern sh_int gsn_scrolls;
extern sh_int gsn_staves;
extern sh_int gsn_wands;
extern sh_int gsn_recall;


/*
 * Utility macros.
 */
#define IS_VALID(data)       ((data) != NULL && (data)->valid)
#define VALIDATE(data)       ((data)->valid = TRUE)
#define INVALIDATE(data)     ((data)->valid = FALSE)
#define UMIN(a, b)           ((a) < (b) ? (a) : (b))
#define UMAX(a, b)           ((a) > (b) ? (a) : (b))
#define URANGE(a, b, c)      ((b) < (a) ? (a) : ((b) > (c) ? (c) : (b)))
#define LOWER(c)             ((c) >= 'A' && (c) <= 'Z' ? (c) + 'a' - 'A' : (c))
#define UPPER(c)             ((c) >= 'a' && (c) <= 'z' ? (c) + 'A' - 'a' : (c))
#define IS_SET(flag, bit)    ((flag) & (bit))
#define SET_BIT(var, bit)    ((var) |= (bit))
#define REMOVE_BIT(var, bit) ((var) &= ~(bit))


/*
 * Character macros.
 */
#define IS_NPC(ch)            (IS_SET((ch)->act, ACT_IS_NPC))
#define IS_IMMORTAL(ch)       (get_trust(ch) >= LEVEL_IMMORTAL)
#define IS_HERO(ch)           (get_trust(ch) >= LEVEL_HERO)
#define IS_TRUSTED(ch, level) (get_trust((ch)) >= (level))
#define IS_AFFECTED(ch, sn)   (IS_SET((ch)->affected_by, (sn)))

#define GET_AGE(ch) ((int)(17 + ((ch)->played + current_time - (ch)->logon) / 72000))

#define IS_GOOD(ch)    ((ch)->alignment >= 350)
#define IS_EVIL(ch)    ((ch)->alignment <= -350)
#define IS_NEUTRAL(ch) (!IS_GOOD(ch) && !IS_EVIL(ch))

#define IS_AWAKE(ch) ((ch)->position > POS_SLEEPING)
#define GET_AC(ch, type) \
    ((ch)->armor[type] + (IS_AWAKE(ch) ? dex_app[get_curr_stat(ch, STAT_DEX)].defensive : 0))
#define GET_HITROLL(ch) ((ch)->hitroll + str_app[get_curr_stat(ch, STAT_STR)].tohit)
#define GET_DAMROLL(ch) ((ch)->damroll + str_app[get_curr_stat(ch, STAT_STR)].todam)

#define IS_OUTSIDE(ch) (!IS_SET((ch)->in_room->room_flags, ROOM_INDOORS))

#define WAIT_STATE(ch, npulse) ((ch)->wait = UMAX((ch)->wait, (npulse)))
#define DAZE_STATE(ch, npulse) ((ch)->daze = UMAX((ch)->daze, (npulse)))
#define get_carry_weight(ch)   ((ch)->carry_weight + (ch)->silver / 10 + (ch)->gold * 2 / 5)

#define act(format, ch, arg1, arg2, type) \
    act_new((format), (ch), (arg1), (arg2), (type), POS_RESTING)

/*
 * Object macros.
 */
#define CAN_WEAR(obj, part)       (IS_SET((obj)->wear_flags, (part)))
#define IS_OBJ_STAT(obj, stat)    (IS_SET((obj)->extra_flags, (stat)))
#define IS_WEAPON_STAT(obj, stat) (IS_SET((obj)->value[4], (stat)))
#define WEIGHT_MULT(obj)          ((obj)->item_type == ITEM_CONTAINER ? (obj)->value[4] : 100)


/*
 * Description macros.
 */
#define PERS(ch, looker) \
    (can_see(looker, (ch)) ? (IS_NPC(ch) ? (ch)->short_descr : (ch)->name) : "someone")

/*
 * Structure for a social in the socials table.
 */
struct social_type {
    char  name[20];
    char *char_no_arg;
    char *others_no_arg;
    char *char_found;
    char *others_found;
    char *vict_found;
    char *char_not_found;
    char *char_auto;
    char *others_auto;
};


/*
 * Global constants.
 */
extern const struct str_app_type str_app[26];
extern const struct int_app_type int_app[26];
extern const struct wis_app_type wis_app[26];
extern const struct dex_app_type dex_app[26];
extern const struct con_app_type con_app[26];

extern const struct class_type   class_table[MAX_CLASS];
extern const struct weapon_type  weapon_table[];
extern const struct item_type    item_table[];
extern const struct wiznet_type  wiznet_table[];
extern const struct attack_type  attack_table[];
extern const struct race_type    race_table[];
extern const struct pc_race_type pc_race_table[];
extern const struct spec_type    spec_table[];
extern const struct liq_type     liq_table[];
extern const struct skill_type   skill_table[MAX_SKILL];
extern const struct group_type   group_table[MAX_GROUP];
extern struct social_type        social_table[MAX_SOCIALS];
extern char *const               title_table[MAX_CLASS][MAX_LEVEL + 1][2];


/*
 * Global variables.
 */
extern HELP_DATA *help_first;
extern HELP_DATA *help_last;

extern SHOP_DATA *shop_first;
extern SHOP_DATA *shop_last;

extern CHAR_DATA       *char_list;
extern DESCRIPTOR_DATA *descriptor_list;
extern OBJ_DATA        *object_list;

extern char           bug_buf[];
extern time_t         current_time;
extern bool           fLogAll;
extern FILE          *fpReserve;
extern KILL_DATA      kill_table[];
extern char           log_buf[];
extern TIME_INFO_DATA time_info;
extern WEATHER_DATA   weather_info;


/*
 * The crypt(3) function is not available on some operating systems.
 * In particular, the U.S. Government prohibits its export from the
 *   United States to foreign countries.
 * Turn on NOCRYPT to keep passwords in plain text.
 */
#if defined(NOCRYPT)
#define crypt(s1, s2) (s1)
#endif


/*
 * Data files used by the server.
 *
 * AREA_LIST contains a list of areas to boot.
 * All files are read in completely at bootup.
 * Most output files (bug, idea, typo, shutdown) are append-only.
 *
 * The NULL_FILE is held open so that we have a stream handle in reserve,
 *   so players can go ahead and telnet to all the other descriptors.
 * Then we close it whenever we need to open a file (e.g. a save file).
 */
#define PLAYER_DIR    "../player/" /* Player files */
#define GOD_DIR       "../gods/"   /* list of gods */
#define TEMP_FILE     "../player/romtmp"
#define NULL_FILE     "/dev/null" /* To reserve one stream */
#define AREA_LIST     "area.lst"  /* List of areas*/
#define BUG_FILE      "bugs.txt"  /* For 'bug' and bug()*/
#define TYPO_FILE     "typos.txt" /* For 'typo'*/
#define NOTE_FILE     "notes.not" /* For 'notes'*/
#define IDEA_FILE     "ideas.not"
#define PENALTY_FILE  "penal.not"
#define NEWS_FILE     "news.not"
#define CHANGES_FILE  "chang.not"
#define SHUTDOWN_FILE "shutdown.txt" /* For 'shutdown'*/
#define BAN_FILE      "ban.txt"
#define MUSIC_FILE    "music.txt"


/*
 * Our function prototypes.
 * One big lump ... this is every function in Merc.
 */
#define CD  CHAR_DATA
#define MID MOB_INDEX_DATA
#define OD  OBJ_DATA
#define OID OBJ_INDEX_DATA
#define RID ROOM_INDEX_DATA
#define SF  SPEC_FUN
#define AD  AFFECT_DATA

/* act_comm.c */
void check_sex(CHAR_DATA *ch);
void add_follower(CHAR_DATA *ch, CHAR_DATA *master);
void stop_follower(CHAR_DATA *ch);
void nuke_pets(CHAR_DATA *ch);
void die_follower(CHAR_DATA *ch);
bool is_same_group(CHAR_DATA *ach, CHAR_DATA *bch);
void fix_sex(CHAR_DATA *ch);

/* act_enter.c */
RID *get_random_room(CHAR_DATA *ch);

/* act_info.c */
void set_title(CHAR_DATA *ch, char *title);

/* act_move.c */
void move_char(CHAR_DATA *ch, int door, bool follow);

/* act_obj.c */
bool can_loot(CHAR_DATA *ch, OBJ_DATA *obj);
void get_obj(CHAR_DATA *ch, OBJ_DATA *obj, OBJ_DATA *container);

/* act_wiz.c */
void wiznet(char *string, CHAR_DATA *ch, OBJ_DATA *obj, long flag, long flag_skip, int min_level);

/* alias.c */
void substitute_alias(DESCRIPTOR_DATA *d, char *input);
void do_alia(CHAR_DATA *ch, char *argument);
void do_alias(CHAR_DATA *ch, char *argument);
void do_unalias(CHAR_DATA *ch, char *argument);

/* ban.c */
#include "ban.h"

/* comm.c */
void show_string(struct descriptor_data *d, char *input);
void close_socket(DESCRIPTOR_DATA *dclose);
void write_to_buffer(DESCRIPTOR_DATA *d, const char *txt, int length);
void send_to_char(const char *txt, CHAR_DATA *ch);
void page_to_char(const char *txt, CHAR_DATA *ch);
void act_new(const char *format, CHAR_DATA *ch, const void *arg1, const void *arg2, int type,
             int min_pos);

/* db.c */
char *print_flags(int flag);
void  boot_db(void);
void  area_update(void);
CD   *create_mobile(MOB_INDEX_DATA *pMobIndex);
void  clone_mobile(CHAR_DATA *parent, CHAR_DATA *clone);
OD   *create_object(OBJ_INDEX_DATA *pObjIndex, int level);
void  clone_object(OBJ_DATA *parent, OBJ_DATA *clone);
void  clear_char(CHAR_DATA *ch);
char *get_extra_descr(const char *name, EXTRA_DESCR_DATA *ed);
MID  *get_mob_index(int vnum);
OID  *get_obj_index(int vnum);
RID  *get_room_index(int vnum);
char  fread_letter(FILE *fp);
int   fread_number(FILE *fp);
long  fread_flag(FILE *fp);
char *fread_string(FILE *fp);
char *fread_string_eol(FILE *fp);
void  fread_to_eol(FILE *fp);
char *fread_word(FILE *fp);
long  flag_convert(char letter);
void *alloc_mem(int sMem);
void *alloc_perm(int sMem);
void  free_mem(void *pMem, int sMem);
char *str_dup(const char *str);
void  free_string(char *pstr);
int   number_fuzzy(int number);
int   number_range(int from, int to);
int   number_percent(void);
int   number_door(void);
int   number_bits(int width);
long  number_mm(void);
int   dice(int number, int size);
int   interpolate(int level, int value_00, int value_32);
void  smash_tilde(char *str);
bool  str_cmp(const char *astr, const char *bstr);
bool  str_prefix(const char *astr, const char *bstr);
bool  str_infix(const char *astr, const char *bstr);
bool  str_suffix(const char *astr, const char *bstr);
char *capitalize(const char *str);
void  append_file(CHAR_DATA *ch, char *file, char *str);
void  bug(const char *str, int param);
void  bugf(const char *str, ...);
void  log_string(const char *str);
void  log_stringf(const char *str, ...);
void  tail_chain(void);

void do_areas(CHAR_DATA *ch, char *argument);
void do_memory(CHAR_DATA *ch, char *argument);
void do_dump(CHAR_DATA *ch, char *argument);
void new_reset(ROOM_INDEX_DATA *pR, RESET_DATA *pReset);

/* effect.c */
void acid_effect(void *vo, int level, int dam, int target);
void cold_effect(void *vo, int level, int dam, int target);
void fire_effect(void *vo, int level, int dam, int target);
void poison_effect(void *vo, int level, int dam, int target);
void shock_effect(void *vo, int level, int dam, int target);


/* fight.c */
bool is_safe(CHAR_DATA *ch, CHAR_DATA *victim);
bool is_safe_spell(CHAR_DATA *ch, CHAR_DATA *victim, bool area);
void violence_update(void);
void multi_hit(CHAR_DATA *ch, CHAR_DATA *victim, int dt);
bool damage(CHAR_DATA *ch, CHAR_DATA *victim, int dam, int dt, int class, bool show);
bool damage_old(CHAR_DATA *ch, CHAR_DATA *victim, int dam, int dt, int class, bool show);
void update_pos(CHAR_DATA *victim);
void stop_fighting(CHAR_DATA *ch, bool fBoth);
void check_killer(CHAR_DATA *ch, CHAR_DATA *victim);

/* flags.c */
void do_flag(CHAR_DATA *ch, char *argument);

/* handler.c */
bool  is_friend(CHAR_DATA *ch, CHAR_DATA *victim);
char *material_name(sh_int num); /* OLC */
AD   *affect_find(AFFECT_DATA *paf, int sn);
void  affect_check(CHAR_DATA *ch, int where, int vector);
int   count_users(OBJ_DATA *obj);
void  deduct_cost(CHAR_DATA *ch, int cost);
void  affect_enchant(OBJ_DATA *obj);
int   check_immune(CHAR_DATA *ch, int dam_type);
int   liq_lookup(const char *name);
int   material_lookup(const char *name);
int   weapon_lookup(const char *name);
int   weapon_type(const char *name);
char *weapon_name(int weapon_Type);
int   item_lookup(const char *name);
char *item_name(int item_type);
int   attack_lookup(const char *name);
int   race_lookup(const char *name);
long  wiznet_lookup(const char *name);
int   class_lookup(const char *name);
bool  is_clan(CHAR_DATA *ch);
bool  is_same_clan(CHAR_DATA *ch, CHAR_DATA *victim);
bool  is_old_mob(CHAR_DATA *ch);
int   get_skill(CHAR_DATA *ch, int sn);
int   get_weapon_sn(CHAR_DATA *ch);
int   get_weapon_skill(CHAR_DATA *ch, int sn);
int   get_age(CHAR_DATA *ch);
void  reset_char(CHAR_DATA *ch);
int   get_trust(CHAR_DATA *ch);
int   get_curr_stat(CHAR_DATA *ch, int stat);
int   get_max_train(CHAR_DATA *ch, int stat);
int   can_carry_n(CHAR_DATA *ch);
int   can_carry_w(CHAR_DATA *ch);
bool  is_name(char *str, char *namelist);
bool  is_exact_name(char *str, char *namelist);
void  affect_to_char(CHAR_DATA *ch, AFFECT_DATA *paf);
void  affect_to_obj(OBJ_DATA *obj, AFFECT_DATA *paf);
void  affect_remove(CHAR_DATA *ch, AFFECT_DATA *paf);
void  affect_remove_obj(OBJ_DATA *obj, AFFECT_DATA *paf);
void  affect_strip(CHAR_DATA *ch, int sn);
bool  is_affected(CHAR_DATA *ch, int sn);
void  affect_join(CHAR_DATA *ch, AFFECT_DATA *paf);
void  char_from_room(CHAR_DATA *ch);
void  char_to_room(CHAR_DATA *ch, ROOM_INDEX_DATA *pRoomIndex);
void  obj_to_char(OBJ_DATA *obj, CHAR_DATA *ch);
void  obj_from_char(OBJ_DATA *obj);
int   apply_ac(OBJ_DATA *obj, int iWear, int type);
OD   *get_eq_char(CHAR_DATA *ch, int iWear);
void  equip_char(CHAR_DATA *ch, OBJ_DATA *obj, int iWear);
void  unequip_char(CHAR_DATA *ch, OBJ_DATA *obj);
int   count_obj_list(OBJ_INDEX_DATA *obj, OBJ_DATA *list);
void  obj_from_room(OBJ_DATA *obj);
void  obj_to_room(OBJ_DATA *obj, ROOM_INDEX_DATA *pRoomIndex);
void  obj_to_obj(OBJ_DATA *obj, OBJ_DATA *obj_to);
void  obj_from_obj(OBJ_DATA *obj);
void  extract_obj(OBJ_DATA *obj);
void  extract_char(CHAR_DATA *ch, bool fPull);
CD   *get_char_room(CHAR_DATA *ch, char *argument);
CD   *get_char_world(CHAR_DATA *ch, char *argument);
OD   *get_obj_type(OBJ_INDEX_DATA *pObjIndexData);
OD   *get_obj_list(CHAR_DATA *ch, char *argument, OBJ_DATA *list);
OD   *get_obj_carry(CHAR_DATA *ch, char *argument, CHAR_DATA *viewer);
OD   *get_obj_wear(CHAR_DATA *ch, char *argument);
OD   *get_obj_here(CHAR_DATA *ch, char *argument);
OD   *get_obj_world(CHAR_DATA *ch, char *argument);
OD   *create_money(int gold, int silver);
int   get_obj_number(OBJ_DATA *obj);
int   get_obj_weight(OBJ_DATA *obj);
int   get_true_weight(OBJ_DATA *obj);
bool  room_is_dark(ROOM_INDEX_DATA *pRoomIndex);
bool  is_room_owner(CHAR_DATA *ch, ROOM_INDEX_DATA *room);
bool  room_is_private(ROOM_INDEX_DATA *pRoomIndex);
bool  can_see(CHAR_DATA *ch, CHAR_DATA *victim);
bool  can_see_obj(CHAR_DATA *ch, OBJ_DATA *obj);
bool  can_see_room(CHAR_DATA *ch, ROOM_INDEX_DATA *pRoomIndex);
bool  can_drop_obj(CHAR_DATA *ch, OBJ_DATA *obj);
char *affect_loc_name(int location);
char *affect_bit_name(int vector);
char *extra_bit_name(int extra_flags);
char *wear_bit_name(int wear_flags);
char *act_bit_name(int act_flags);
char *off_bit_name(int off_flags);
char *imm_bit_name(int imm_flags);
char *form_bit_name(int form_flags);
char *part_bit_name(int part_flags);
char *weapon_bit_name(int weapon_flags);
char *comm_bit_name(int comm_flags);
char *cont_bit_name(int cont_flags);

/* healer.c */
void do_heal(CHAR_DATA *ch, char *argument);

/* interp.c */
void  interpret(CHAR_DATA *ch, char *argument);
bool  is_number(char *arg);
int   number_argument(char *argument, char *arg);
int   mult_argument(char *argument, char *arg);
char *one_argument(char *argument, char *arg_first);

/* magic.c */
int  find_spell(CHAR_DATA *ch, const char *name);
int  mana_cost(CHAR_DATA *ch, int min_mana, int level);
int  skill_lookup(const char *name);
int  slot_lookup(int slot);
bool saves_spell(int level, CHAR_DATA *victim, int dam_type);
bool saves_dispel(int dis_level, int spell_level, int duration);
bool check_dispel(int dis_level, CHAR_DATA *victim, int sn);
void obj_cast_spell(int sn, int level, CHAR_DATA *ch, CHAR_DATA *victim, OBJ_DATA *obj);

/* music.c */
void do_play(CHAR_DATA *ch, char *argument);

/* note.c */
void do_unread(CHAR_DATA *ch, char *argument);
void do_note(CHAR_DATA *ch, char *argument);
void do_idea(CHAR_DATA *ch, char *argument);
void do_penalty(CHAR_DATA *ch, char *argument);
void do_news(CHAR_DATA *ch, char *argument);
void do_changes(CHAR_DATA *ch, char *argument);
void load_notes(void);

/* save.c */
void save_char_obj(CHAR_DATA *ch);
bool load_char_obj(DESCRIPTOR_DATA *d, char *name);

/* scan.c */
void do_scan(CHAR_DATA *ch, char *argument);

/* skills.c */
bool parse_gen_groups(CHAR_DATA *ch, char *argument);
void list_group_costs(CHAR_DATA *ch);
void list_group_known(CHAR_DATA *ch);
int  exp_per_level(CHAR_DATA *ch, int points);
void check_improve(CHAR_DATA *ch, int sn, bool success, int multiplier);
int  group_lookup(const char *name);
void gn_add(CHAR_DATA *ch, int gn);
void gn_remove(CHAR_DATA *ch, int gn);
void group_add(CHAR_DATA *ch, const char *name, bool deduct);
void group_remove(CHAR_DATA *ch, const char *name);

/* special.c */
SF   *spec_lookup(const char *name);
char *spec_name(SPEC_FUN *function);

/* teleport.c */
RID *room_by_name(char *target, int level, bool error);

/* update.c */
void advance_level(CHAR_DATA *ch, bool hide);
void gain_exp(CHAR_DATA *ch, int gain);
void gain_condition(CHAR_DATA *ch, int iCond, int value);
void update_handler(void);

#undef CD
#undef MID
#undef OD
#undef OID
#undef RID
#undef SF
#undef AD

/*****************************************************************************
 *                                    OLC                                    *
 *****************************************************************************/
/*
 * This structure is used in bit.c to lookup flags and stats.
 */
struct flag_type {
    char *name;
    int   bit;
    bool  settable;
};

/*
 * Object defined in limbo.are
 * Used in save.c to load objects that don't exist.
 */
#define OBJ_VNUM_DUMMY 1

/*
 * Area flags.
 */
#define AREA_NONE    0
#define AREA_CHANGED 1 /* Area has been modified. */
#define AREA_ADDED   2 /* Area has been added to. */
#define AREA_LOADING 4 /* Used for counting in db.c */


#define MAX_DIR 6
#define NO_FLAG (-99) /* Must not be used in flags or stats. */


/*
 * Interp.c
 */
DECLARE_DO_FUN(do_olc);
DECLARE_DO_FUN(do_asave);
DECLARE_DO_FUN(do_alist);
DECLARE_DO_FUN(do_resets);


/*
 * Global Constants
 */
extern char *const            dir_name[];
extern const sh_int           rev_dir[]; /* sh_int - ROM OLC */
extern const struct spec_type spec_table[];


/*
 * Global variables
 */
extern AREA_DATA *area_first;
extern AREA_DATA *area_last;
extern SHOP_DATA *shop_last;

extern int top_affect;
extern int top_area;
extern int top_ed;
extern int top_exit;
extern int top_help;
extern int top_mob_index;
extern int top_obj_index;
extern int top_reset;
extern int top_room;
extern int top_shop;

extern int top_vnum_mob;
extern int top_vnum_obj;
extern int top_vnum_room;

extern char str_empty[1];

extern MOB_INDEX_DATA  *mob_index_hash[MAX_KEY_HASH];
extern OBJ_INDEX_DATA  *obj_index_hash[MAX_KEY_HASH];
extern ROOM_INDEX_DATA *room_index_hash[MAX_KEY_HASH];


/* act_wiz.c */
/*
ROOM_INDEX_DATA *find_location( CHAR_DATA *ch, char *arg );
*/
/* db.c */
void reset_area(AREA_DATA *pArea);
void reset_room(ROOM_INDEX_DATA *pRoom);

/* string.c */
void  string_edit(CHAR_DATA *ch, char **pString);
void  string_append(CHAR_DATA *ch, char **pString);
char *string_replace(char *orig, char *old, char *new);
void  string_add(CHAR_DATA *ch, char *argument);
char *format_string(char *oldstring /*, bool fSpace */);
char *first_arg(char *argument, char *arg_first, bool fCase);
char *string_unpad(char *argument);
char *string_proper(char *argument);

/* olc.c */
bool  run_olc_editor(DESCRIPTOR_DATA *d);
char *olc_ed_name(CHAR_DATA *ch);
char *olc_ed_vnum(CHAR_DATA *ch);

/* special.c */
char *spec_string(SPEC_FUN *fun); /* OLC */

/* bit.c */
extern const struct flag_type area_flags[];
extern const struct flag_type sex_flags[];
extern const struct flag_type exit_flags[];
extern const struct flag_type door_resets[];
extern const struct flag_type room_flags[];
extern const struct flag_type sector_flags[];
extern const struct flag_type type_flags[];
extern const struct flag_type extra_flags[];
extern const struct flag_type wear_flags[];
extern const struct flag_type act_flags[];
extern const struct flag_type affect_flags[];
extern const struct flag_type apply_flags[];
extern const struct flag_type wear_loc_strings[];
extern const struct flag_type wear_loc_flags[];
extern const struct flag_type weapon_flags[];
extern const struct flag_type container_flags[];
extern const struct flag_type liquid_flags[];

/* ROM OLC: */

extern const struct flag_type material_type[];
extern const struct flag_type form_flags[];
extern const struct flag_type part_flags[];
extern const struct flag_type ac_type[];
extern const struct flag_type size_flags[];
extern const struct flag_type off_flags[];
extern const struct flag_type imm_flags[];
extern const struct flag_type res_flags[];
extern const struct flag_type vuln_flags[];
extern const struct flag_type position_flags[];
extern const struct flag_type weapon_class[];
extern const struct flag_type weapon_type_olc[];


/*****************************************************************************
 *                                 OLC END                                   *
 *****************************************************************************/

#if defined(__cplusplus)
}
#endif

#endif /* _ROM_MERC_H_ */
