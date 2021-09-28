//
// Created by vini84200 on 28/09/2021.
//

#include "menuController.h"

void updateMenu(struct Menu *self, double delta) {
    self->fps = (float) (1 / delta);
}

void enter_menu(struct Menu *self) {
    self->janela = newwin(getmaxy(stdscr) - 8, getmaxx(stdscr) - 8, 4, 4);
    box(self->janela, 0, 0);

    wrefresh(self->janela);
}

void leave_menu(struct Menu *self) {
    wborder(self->janela, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
    wrefresh(self->janela);
    delwin(self->janela);
}

void abrirTela(struct Menu *self, enum MENU_TELA novaTela) {
    self->telaAberta = novaTela;
    werase(self->janela);
}

void fechaTela(struct Menu *self) {
    abrirTela(self, T_INICIAL);
}