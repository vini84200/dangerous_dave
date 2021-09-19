cmake_minimum_required (VERSION 3.20)
project (DDave VERSION 0.1)
set(CMAKE_C_STANDARD 11)

set(SOURCE_FILES src/main.c src/erros.c src/erros.h src/AppStateMachine.c src/AppStateMachine.h)
add_compile_options("$<$<CONFIG:DEBUG>:-DDEBUG>")

configure_file(config.h.in config.h)

add_executable (DDave ${SOURCE_FILES})

target_link_libraries(DDave ncurses tinfo)

target_include_directories(DDave PUBLIC
        "${PROJECT_BINARY_DIR}"
        )