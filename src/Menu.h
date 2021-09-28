#pragma once
#include "core.h"
#include "controller/AppStateMachine.h"

#define MENU_HEIGHT 9
#define MIN_Y MENU_HEIGHT + 0

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

// Desenhar

void drawMenu(struct Menu*);

void escreverCentralizado(WINDOW* w, const char *palavra, int y);

void escreverTitulo(WINDOW * w, int y);

void  escreverOpcao(WINDOW * w, char* text, bool selecionado, int y);

// Trata as entradas de um menu, retorna se a entrada foi tratada.
bool handleInputMenu(struct Menu* self, int ch);

void updateMenu(struct Menu* self, double delta);

void enter_menu(struct Menu*);

void leave_menu(struct Menu*);

// Abre uma tela sobre o menu.
void abrirTela(struct Menu*, enum MENU_TELA);

// Fecha tela, e volta ao menu Inicial
void fechaTela(struct Menu*);