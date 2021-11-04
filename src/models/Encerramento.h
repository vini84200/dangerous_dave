#pragma once

#include "../controller/AppStateMachine.h"
#include "game.h"

#define ESTADO_INICIAL      0
#define ESTADO_PEDINDO_NOME 1
#define ESTADO_SALVANDO     2
#define ESTADO_FINAL        3


struct Encerramento {
    struct AppStateMachine *ASM;
    int estado;
    int foi_pro_rank;
    char nome[20];
    bool modoDeEscrita;
    int ptr_digitacao;
};


struct Encerramento *newEncerramento(struct AppStateMachine *novaASM);

void destroyEncerramento(struct Encerramento *self);
