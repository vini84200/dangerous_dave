#pragma once
#include <ncurses.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

// Arquivo gerado pelo CMake
#include "config.h"

#ifdef DEBUG

#elif
#define LOG(args)
#define WARN(args)

#endif

// Por algum motivo, o nCurses não define o código do esc
#define KEY_ESC 27

