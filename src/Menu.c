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
    int maxY = getmaxy(stdscr);
    erase();
    if(maxY<=MIN_Y) errorClose("Tela muito pequena!");
    int centroY = maxY / 2;
    int startMenuY = centroY - (MENU_HEIGHT/2);

    escreverTitulo(startMenuY);
    // +3
    escreverOpcao("Novo Jogo", self->selecionado == 0, startMenuY+3);
    escreverOpcao("Carregar", self->selecionado == 1, startMenuY+4);
    escreverOpcao("Ranking", self->selecionado == 2, startMenuY+5);
    escreverOpcao("Sair", self->selecionado == 3, startMenuY+6);

#ifdef DEBUG
    char* txt_debug [40];
    snprintf(txt_debug, 40, "Selecionado: %d | FPS: %4.3f", self->selecionado, self->fps);
    escreverCentralizado(txt_debug, 0);
#endif
}

void escreverCentralizado(const char *palavra, int y) {
    int x = getmaxx(stdscr);
    int centro = x/2;

    move(y, centro - strlen(palavra) / 2);
    printw(palavra);
}

void escreverTitulo(int y) {
    attron(A_BOLD);
    escreverCentralizado(" DANGEROUS ", y);
    escreverCentralizado("      DAVE ",  y+1);
    attroff(A_BOLD);
}

void escreverOpcao(char *text, bool selecionado, int y) {
    if (selecionado) {

        char *selectedLine[30];
        strcat(selectedLine, "*<");
        strcat(selectedLine, text);
        strcat(selectedLine, ">* ");
        attron(A_UNDERLINE | A_BOLD);
        escreverCentralizado(selectedLine, y);
        attroff(A_UNDERLINE | A_BOLD);
    } else {
        escreverCentralizado(text, y);
    }
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
            if (self->selecionado >= MENU_OPCOES) self->selecionado = MENU_OPCOES-1;
            return TRUE;
        case KEY_UP:
            self->selecionado--;
            if (self->selecionado < 0) self->selecionado = 0;
            return TRUE;
        case KEY_ENTER:
            break;
    }
    return FALSE;
}

void destroyMenu(struct Menu * menu) {
    free(menu);
}

void updateMenu(struct Menu *self, double delta) {
    self->fps = (float) (1/delta);
}



