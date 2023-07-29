ROM_EXE = rom

LUA_VERSION = lua-5.4.6
LUA_INSTALL_DIR = $(CURDIR)/lib/lua
LUA_LIB = $(LUA_INSTALL_DIR)/lib/liblua.a

DEPS = $(LUA_LIB)
MKDIR = mkdir -p
CURL = curl -R -O

rom: $(DEPS)
	cd src && $(MAKE) rom

$(LUA_LIB): $(LUA_VERSION)/Makefile
	$(MKDIR) lib/lua
	cd $(LUA_VERSION) && $(MAKE) linux install INSTALL_TOP=$(LUA_INSTALL_DIR)

$(LUA_VERSION)/Makefile:
	$(CURL) http://www.lua.org/ftp/$(LUA_VERSION).tar.gz
	tar zxf $(LUA_VERSION).tar.gz
	$(RM) $(LUA_VERSION).tar.gz

clean:
	$(RM) $(ROM_EXE)
	cd src && $(MAKE) clean

fullclean: clean
	$(RM) -r lib/lua
	cd $(LUA_VERSION) && $(MAKE) clean

.PHONY: rom clean fullclean
