#include "Menu.h"


struct Menu *newMenu(struct AppStateMachine *novaASM) {
    struct Menu *menu = malloc(sizeof(struct Menu));
    menu->selecionado = 0;
    menu->ASM = novaASM;
    menu->telaAberta = T_INICIAL;
    menu->janela = NULL;
    return menu;
}

void destroyMenu(struct Menu *menu) {
    free(menu);
}




