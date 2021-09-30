cmake_minimum_required (VERSION 3.16)

project(DDave
        VERSION 0.2
        LANGUAGES C)
set(CMAKE_C_STANDARD 11)

set(SOURCE_FILES
        src/main.c
        src/utils/erros.c
        src/controller/AppStateMachine.c
        src/models/Menu.c
        src/controller/gameController.c
        src/models/Entidade.c
        src/views/gameView.c
        src/models/game.c
        src/controller/menuController.c
        src/views/MenuView.c
        src/models/ranking.c
        src/views/encerramentoView.c
        src/models/Encerramento.c
        )
add_compile_options("$<$<CONFIG:DEBUG>:-DDEBUG>")

configure_file(config.h.in config.h)

add_executable (DDave ${SOURCE_FILES})

# Verifica e Inclui o Ncurses
set(CURSES_NEED_NCURSES TRUE)
find_package(Curses REQUIRED)
if (CURSES_FOUND AND CURSES_HAVE_NCURSES_H)
    include_directories(${CURSES_INCLUDE_DIR})
    target_link_libraries (DDave ${CURSES_LIBRARIES})
endif()

target_link_libraries(DDave ncurses tinfo)

target_include_directories(DDave PUBLIC
        "${PROJECT_BINARY_DIR}"
        )

file(COPY assets/ DESTINATION ${CMAKE_BINARY_DIR}/assets)