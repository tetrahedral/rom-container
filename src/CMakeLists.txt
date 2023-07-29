cmake_minimum_required(VERSION 3.20)

project(ContainerROM VERSION 2.4.1 LANGUAGES C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(gcc_like_c $<COMPILE_LANG_AND_ID:C,ARMClang,AppleClang,Clang,GNU>)

file(GLOB rom_SOURCES CONFIGURE_DEPENDS "*.h" "*.c")

add_executable(rom ${rom_SOURCES})

target_compile_options(rom
    PRIVATE $<${gcc_like_c}:-Wall;-Wextra;-pedantic;-Werror;-Wno-unused-parameter;-Wno-unused-variable;-Wno-unused-function;-Wmissing-prototypes;-Wstrict-prototypes;-g>
)

add_library(lua STATIC IMPORTED)
set_target_properties(lua PROPERTIES IMPORTED_LOCATION ../lib/lua/lib/liblua.a)
target_include_directories(lua INTERFACE ../lib/lua/include)
target_link_libraries(rom PRIVATE lua)
