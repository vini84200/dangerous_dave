#include "Menu.h"
#include "AppStateMachine.h"
#include "erros.h"

struct Menu *newMenu(struct AppStateMachine *novaASM) {
    struct Menu *menu = malloc(sizeof(struct Menu));
    menu->selecionado = 0;
    menu->ASM = novaASM;
    return menu;
}


void drawMenu(struct Menu *self) {
    erase();
    escreverCentralizado("MENU!", 0);
    escreverCentralizado("MENU!", 1);
    char* txt_selecionado [30];
    snprintf(txt_selecionado, 30, "Selecionado: %d", self->selecionado);
    escreverCentralizado(txt_selecionado, 3);
    char* txt_fps [14];
    snprintf(txt_fps, 14,"FPS: %4.3f", self->fps);
    escreverCentralizado(txt_fps, 4);
}

void escreverCentralizado(const char *palavra, int y) {
    int x = getmaxx(stdscr);
    int centro = x/2;

    move(y, centro - strlen(palavra) / 2);
    printw(palavra);
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

void destroyMenu(struct Menu * menu) {
    free(menu);
}

void updateMenu(struct Menu *self, double delta) {
    self->fps = (float) (1/delta);
}

