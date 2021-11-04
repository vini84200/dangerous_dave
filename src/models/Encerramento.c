#include "../core.h"
#include "Encerramento.h"

void destroyEncerramento(struct Encerramento *self) {
    free(self);
}

struct Encerramento *newEncerramento(struct AppStateMachine *novaASM) {
    struct Encerramento *ptr = malloc(sizeof(struct Encerramento));
    ptr->ASM = novaASM;
    ptr->estado = ESTADO_INICIAL;
    ptr->foi_pro_rank = 0;
    ptr->modoDeEscrita = false;
    ptr->ptr_digitacao = 0;
    return ptr;
}