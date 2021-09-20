#pragma once
#include "core.h"
#include "AppStateMachine.h"

struct Menu{
    int selecionado;
    struct AppStateMachine *ASM;
};

struct Menu *newMenu(struct AppStateMachine *novaASM);

void drawMenu(struct Menu*);

// Trata as entradas de um menu, retorna se a entrada foi tratada.
bool handleInputMenu(struct Menu* self, int ch);

