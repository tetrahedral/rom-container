ROM_EXE = rom
LUA_DIR = ../lib/lua

CC       = gcc
PROF     = -g
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
		mem.o bit.o olc.o olc_act.o olc_save.o script_api.o scripting.o

rom: $(O_FILES)
	$(CC) $(LFLAGS) -o $(ROM_EXE) $(O_FILES) $(LIBS)
	chmod +x rom

act_comm.o: merc.h interp.h recycle.h tables.h
act_enter.o: merc.h interp.h
act_info.o: merc.h interp.h magic.h recycle.h tables.h lookup.h
act_move.o: merc.h interp.h
act_obj.o: merc.h interp.h
act_wiz.o: act_wiz.h merc.h interp.h recycle.h tables.h lookup.h
alias.o: merc.h
ban.o: ban.h merc.h recycle.h
bit.o: bit.h merc.h lookup.h
comm.o: merc.h interp.h olc.h recycle.h tables.h telnet.h
const.o: merc.h interp.h magic.h
db.o: db.h merc.h recycle.h music.h lookup.h
db.h: merc.h
db2.o: db.h merc.h lookup.h
effects.o: merc.h recycle.h
fight.o: merc.h interp.h
flags.o: merc.h lookup.h tables.h
handler.o: merc.h interp.h magic.h recycle.h tables.h
healer.o: merc.h magic.h
interp.o: interp.h merc.h olc.h
interp.h: merc.h
lookup.o: lookup.h merc.h tables.h
magic.o: magic.h merc.h interp.h recycle.h db.h
magic.h: merc.h
magic2.o: magic.h merc.h interp.h
mem.o: merc.h olc.h
music.o: music.h merc.h recycle.h
note.o: merc.h recycle.h tables.h db.h
olc_act.o: olc.h merc.h tables.h lookup.h
olc_save.o: olc.h merc.h tables.h lookup.h
olc.o: olc.h merc.h
olc.h: merc.h
recycle.o: recycle.h merc.h
recycle.h: merc.h
save.o: merc.h recycle.h tables.h lookup.h
scan.o: merc.h
script_api.o: script_api.h merc.h
scripting.o: scripting.h script_api.h merc.h
skills.o: merc.h interp.h magic.h recycle.h
special.o: merc.h interp.h magic.h db.h
string.o: merc.h
tables.o: tables.h merc.h
tables.h: merc.h
update.o: merc.h interp.h music.h

%.o: %.c %.h merc.h
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< $(OUTPUT_OPTION)

clean:
	$(RM) $(ROM_EXE) *.o

.PHONY: clean
