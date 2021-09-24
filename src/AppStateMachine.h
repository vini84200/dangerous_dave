#pragma once
#include "core.h"
#include "Menu.h"

typedef enum {
    MENU,
    IN_GAME,
    ENCERRAMENTO
} AppState;

struct AppStateMachine {
    AppState estado;
    bool executar;
    struct Menu* menu;
    struct Game* game;
};

// Atualiza o estado de uma ASM
void ASM_mudarEstado(struct AppStateMachine *self, AppState newState);

// Cria uma AppStateMachine no Menu
struct AppStateMachine* ASM_newASM();

// Recebe as teclas que são pressionadas para alterar seus estados. Retorna se a tecla foi tratada.
bool ASM_handleInput(struct AppStateMachine *self, int ch);

// Imprime na tela o jogo, respeitando seu estado atual
void ASM_draw(struct AppStateMachine *self);

// Loop de Updates
void ASM_update(struct AppStateMachine *self, double delta);

void destroyASM(struct AppStateMachine*);