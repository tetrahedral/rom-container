ROM_EXE = rom
LUA_DIR = ../lib/lua

CC       = gcc
PROF     = -O -g
NOCRYPT  =

CFLAGS   = -std=gnu99 -Wall -Wextra -pedantic -Wmissing-prototypes -Wstrict-prototypes -Wno-unused-parameter \
 -Wno-unused-function $(PROF) $(NOCRYPT)

CPPFLAGS = -Dunix -Dlinux -I$(LUA_DIR)/include

LFLAGS   = $(PROF)

LIBS	 = -L$(LUA_DIR)/lib -llua -lcrypt

O_FILES = act_comm.o act_enter.o act_info.o act_move.o act_obj.o act_wiz.o \
		alias.o ban.o comm.o const.o db.o db2.o effects.o fight.o flags.o \
		handler.o healer.o interp.o note.o lookup.o magic.o magic2.o music.o \
		recycle.o save.o scan.o skills.o special.o tables.o update.o string.o \
		mem.o bit.o olc.o olc_act.o olc_save.o scripting.o

%.o: %.c %.h merc.h
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< $(OUTPUT_OPTION)

rom: $(O_FILES)
	$(CC) $(LFLAGS) -o $(ROM_EXE) $(O_FILES) $(LIBS)

clean:
	$(RM) $(ROM_EXE) *.o
