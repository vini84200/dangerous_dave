#pragma once

#include "../controller/AppStateMachine.h"
#include "game.h"

struct Encerramento {
    struct AppStateMachine *ASM;
};


struct Encerramento *newEncerramento(struct AppStateMachine *novaASM);

void destroyEncerramento(struct Encerramento *self);
