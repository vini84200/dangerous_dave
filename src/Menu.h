#pragma once
#include "core.h"
#include "AppStateMachine.h"

#define MENU_HEIGHT 9
#define MIN_Y MENU_HEIGHT + 6

#define MENU_OPCOES 4

struct Menu{
    int selecionado;
    struct AppStateMachine *ASM;
    float fps;
};

// F. Básicas

struct Menu *newMenu(struct AppStateMachine *novaASM);

void destroyMenu(struct Menu*);

// Desenhar

void drawMenu(struct Menu*);

void escreverCentralizado(const char *palavra, int y);

void escreverTitulo(int y);

void  escreverOpcao(char* text, bool selecionado, int y);

// Trata as entradas de um menu, retorna se a entrada foi tratada.
bool handleInputMenu(struct Menu* self, int ch);

void updateMenu(struct Menu* self, double delta);