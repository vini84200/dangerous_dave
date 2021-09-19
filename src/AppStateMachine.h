#pragma once
#include "core.h"

typedef enum {
    MENU,
    IN_GAME,
    ENCERRAMENTO
} AppState;

typedef struct {
    AppState estado;
    bool executar;
} AppStateMachine;

// Atualiza o estado de uma ASM
void ASM_mudarEstado(AppStateMachine * self, AppState newState);

// Cria uma AppStateMachine no Menu
AppStateMachine ASM_newASM();

// Recebe as teclas que são pressionadas para alterar seus estados. Retorna se a tecla foi tratada.
bool ASM_handleInput(AppStateMachine * self, int ch);

// Imprime na tela o jogo, respeitando seu estado atual
void ASM_draw(AppStateMachine * self);