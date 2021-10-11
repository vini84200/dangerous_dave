#pragma once

#include "../core.h"
#include "../models/Menu.h"
#include "../models/Encerramento.h"

typedef enum {
    INICIANDO,
    MENU,
    IN_GAME,
    ENCERRAMENTO
} AppState;

struct AppStateMachine {
    AppState estado;
    bool executar;
    struct Menu *menu;
    struct Game *game;
    struct Encerramento *encerramento;
};

// Atualiza o estado de uma ASM
void mudarEstado(struct AppStateMachine *self, AppState newState);

// Cria uma AppStateMachine no Menu
struct AppStateMachine *newASM();

// Recebe as teclas que são pressionadas para alterar seus estados. Retorna se a tecla foi tratada.
bool ASM_handleInput(struct AppStateMachine *self, int ch);

// Imprime na tela o jogo, respeitando seu estado atual
void ASM_draw(struct AppStateMachine *self);

// Loop de Updates
void ASM_update(struct AppStateMachine *self, double delta);

void destroyASM(struct AppStateMachine *);