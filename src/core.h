#pragma once

#include "stdio.h"

#ifdef DEBUG

#elif
#define LOG(args)
#define WARN(args)

#endif

// Por algum motivo, o nCurses não define o código do esc
#define KEY_ESC 27

