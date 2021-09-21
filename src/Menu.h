#pragma once
#include "core.h"
#include "AppStateMachine.h"

struct Menu{
    int selecionado;
    struct AppStateMachine *ASM;
    float fps;
};

struct Menu *newMenu(struct AppStateMachine *novaASM);

void destroyMenu(struct Menu*);

void drawMenu(struct Menu*);

void escreverCentralizado(const char *palavra, int y);

// Trata as entradas de um menu, retorna se a entrada foi tratada.
bool handleInputMenu(struct Menu* self, int ch);

void updateMenu(struct Menu* self, double delta);