cmake_minimum_required (VERSION 3.20)
project (DDave)
set(CMAKE_C_STANDARD 11)

set(SOURCE_FILES src/main.c src/erros.c src/erros.h)
add_compile_options("$<$<CONFIG:DEBUG>:-DDEBUG>")


add_executable (DDave ${SOURCE_FILES})

target_link_libraries(DDave ncurses tinfo)