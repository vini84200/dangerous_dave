#pragma once
#include <ncurses.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

// Arquivo gerado pelo CMake
#include "config.h"

// Por algum motivo, o nCurses não define o código do esc
#define KEY_ESC 27

#define FPS_LIMIT 170
