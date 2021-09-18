cmake_minimum_required (VERSION 3.13)
project (DDave)
set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES src/main.c)
add_compile_options("$<$<CONFIG:DEBUG>:-DDEBUG>")


add_executable (DDave ${SOURCE_FILES})

target_link_libraries(DDave ncurses tinfo)