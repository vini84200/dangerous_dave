#pragma once

#include "../models/Menu.h"

void updateMenu(struct Menu *self, double delta);

void enter_menu(struct Menu *);

void leave_menu(struct Menu *);

// Abre uma tela sobre o menu.
void abrirTela(struct Menu *, enum MENU_TELA);

// Fecha tela, e volta ao menu Inicial
void fechaTela(struct Menu *);