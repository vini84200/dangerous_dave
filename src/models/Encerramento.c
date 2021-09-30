#include "../core.h"
#include "Encerramento.h"

void destroyEncerramento(struct Encerramento *self) {
    free(self);
}

struct Encerramento *newEncerramento(struct AppStateMachine *novaASM) {
    struct Encerramento *ptr = malloc(sizeof(struct Encerramento));
    ptr->ASM = novaASM;
    return ptr;
}