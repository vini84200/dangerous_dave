#include "Menu.h"
#include "AppStateMachine.h"

struct Menu *newMenu(struct AppStateMachine *novaASM) {
    struct Menu *menu = malloc(sizeof(struct Menu));
    menu->selecionado = 0;
    menu->ASM = novaASM;
    return menu;
}

void drawMenu(struct Menu *self) {
    printw("MENU!\n");
    printw("Selecionado: %d\n", self->selecionado);
}

bool handleInputMenu(struct Menu *self, int ch) {
    switch (ch) {
        case KEY_BACKSPACE:
            printw("handleInputMenu: %h \n",self);
            printw("handleInputMenu: %h \n",self->ASM);
            ASM_mudarEstado(self->ASM, IN_GAME);
            return TRUE;
        case KEY_DOWN:
            self->selecionado++;
            return TRUE;
        case KEY_UP:
            self->selecionado--;
            return TRUE;
    }
    return FALSE;
}

