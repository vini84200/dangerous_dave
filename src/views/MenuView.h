#pragma once

#include "../core.h"
#include "../models/Menu.h"
#include "../utils/erros.h"
#include "../controller/AppStateMachine.h"
#include "../controller/menuController.h"
#include "../models/ranking.h"
#include "../controller/gameController.h"

#define MENU_HEIGHT 9
#define MIN_Y (MENU_HEIGHT)

void drawMenu(struct Menu *);

void escreverCentralizado(struct _win_st *window, const char *palavra, int linha);

void escreverTitulo(struct _win_st *window, int linha);

void escreverOpcao(struct _win_st *window, char *text, bool selecionado, int linha);

bool handleInputMenu(struct Menu *self, int ch);