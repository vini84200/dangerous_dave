#pragma once
#include <ncurses.h>

#define TAMANHOY 30
#define TAMANHOX 120

void drawElement(char elemento, int color);
void drawMap(char vetor[TAMANHOY][TAMANHOX]);
void header();
void game();





