#ifndef _ROM_ASCII_BITS_H_
#define _ROM_ASCII_BITS_H_

/* RT ASCII conversions -- used so we can have letters in this file */

#define A (1<<0)
#define B (1<<1)
#define C (1<<2)
#define D (1<<3)
#define E (1<<4)
#define F (1<<5)
#define G (1<<6)
#define H (1<<7)

#define I (1<<8)
#define J (1<<9)
#define K (1<<10)
#define L (1<<11)
#define M (1<<12)
#define N (1<<13)
#define O (1<<14)
#define P (1<<15)

#define Q (1<<16)
#define R (1<<17)
#define S (1<<18)
#define T (1<<19)
#define U (1<<20)
#define V (1<<21)
#define W (1<<22)
#define X (1<<23)

#define Y  (1<<24)
#define Z  (1<<25)
#define aa (1<<26) /* doubled due to conflicts */
#define bb (1<<27)
#define cc (1<<28)
#define dd (1<<29)
#define ee (1<<30)

/* for command types */
#define ML MAX_LEVEL       /* implementor */
#define L1 (MAX_LEVEL - 1) /* creator */
#define L2 (MAX_LEVEL - 2) /* supreme being */
#define L3 (MAX_LEVEL - 3) /* deity */
#define L4 (MAX_LEVEL - 4) /* god */
#define L5 (MAX_LEVEL - 5) /* immortal */
#define L6 (MAX_LEVEL - 6) /* demigod */
#define L7 (MAX_LEVEL - 7) /* angel */
#define L8 (MAX_LEVEL - 8) /* avatar */
#define IM LEVEL_IMMORTAL  /* avatar */
#define HE LEVEL_HERO      /* hero */

#endif
