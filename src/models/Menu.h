#pragma once

#include "../core.h"
#include "../controller/AppStateMachine.h"

#define NOVO_JOGO   0
#define CARREGAR    1
#define RANK        2
#define SAIR        3
#define MENU_OPCOES 4

enum MENU_TELA {
    T_INICIAL = 0,
    T_CARREGAR = 1,
    T_RANK = 2,
};

struct Menu {
    int selecionado;
    struct AppStateMachine *ASM;
    float fps;
    enum MENU_TELA telaAberta;
    WINDOW * janela;
};

// F. Básicas

struct Menu *newMenu(struct AppStateMachine *novaASM);

void destroyMenu(struct Menu*);

