#pragma once

#include "../core.h"
#include "../models/Menu.h"
#include "../utils/erros.h"
#include "../controller/AppStateMachine.h"
#include "../controller/menuController.h"
#include "../models/ranking.h"
#include "../controller/gameController.h"

#define MENU_HEIGHT 9
#define MIN_Y MENU_HEIGHT + 0

void drawMenu(struct Menu *);

void escreverCentralizado(struct _win_st *w, const char *palavra, int y);

void escreverTitulo(struct _win_st *w, int y);

void escreverOpcao(struct _win_st *w, char *text, bool selecionado, int y);

bool handleInputMenu(struct Menu *self, int ch);