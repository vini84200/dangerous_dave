cmake_minimum_required (VERSION 3.16)

project(DDave
        VERSION 0.2
        LANGUAGES C)
set(CMAKE_C_STANDARD 11)

file(GLOB SOURCE_FILES
        src/**.c
        src/utils/*.c
        src/controller/*.c
        src/models/*.c
        src/views/*.c
        )

file(GLOB LIBRARIES
        extern/tpl/src/tpl.c)

add_compile_options("$<$<CONFIG:DEBUG>:-DDEBUG>")

configure_file(config.h.in config.h)

add_executable(DDave ${SOURCE_FILES} ${LIBRARIES})

# Verifica e Inclui o Ncurses
set(CURSES_NEED_NCURSES TRUE)
find_package(Curses REQUIRED)
if (CURSES_FOUND AND CURSES_HAVE_NCURSES_H)
    include_directories(${CURSES_INCLUDE_DIR})
    target_link_libraries (DDave ${CURSES_LIBRARIES})
endif()

target_link_libraries(DDave ncurses tinfo m)

target_include_directories(DDave PUBLIC
        "${PROJECT_BINARY_DIR}"
        src
        extern/tpl/src

        )

# Copia assets para a pasta compilada
#file(COPY assets/ DESTINATION ${CMAKE_BINARY_DIR}/assets)
add_custom_command(
        TARGET DDave PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets
        ${CMAKE_BINARY_DIR}/assets)

if (UNIX AND NOT APPLE)
    set(LINUX TRUE)
endif ()

if (LINUX)
    message(STATUS "Linux")
    add_custom_command(
            TARGET DDave PRE_BUILD
            COMMAND ${CMAKE_COMMAND} -E make_directory "~/.local/share/DDave/"
    )
endif ()

find_package(Git QUIET)
if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
# Update submodules as needed
    option(GIT_SUBMODULE "Check submodules during build" ON)
    if(GIT_SUBMODULE)
        message(STATUS "Submodule update")
        execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
                        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                        RESULT_VARIABLE GIT_SUBMOD_RESULT)
        if(NOT GIT_SUBMOD_RESULT EQUAL "0")
            message(FATAL_ERROR "git submodule update --init --recursive failed with ${GIT_SUBMOD_RESULT}, please checkout submodules")
        endif()
    endif()
endif()
