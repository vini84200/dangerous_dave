//
// Created by vini84200 on 30/09/2021.
//

#include "encerramentoView.h"

void viewEncerramento(struct Encerramento *self) {
    char *message;

    if (self->ASM->game->resultado == VITORIA) {
        message = "PARABENS! Você venceu todas as fases!";
    }
    if (self->ASM->game->resultado == DERROTA) {
        message = "GAME OVER! Você perdeu todas as suas vidas.";
    }

    move(2, 2);
    printw(message);
    move(3, 2);
    printw("Pontuação final: %04d", self->ASM->game->pontuacao);
    //TODO Adiciona rank aqui
}

bool handleInputEncerramento(struct Encerramento *self, int ch) {
    switch (ch) {
        case KEY_ESC:
            mudarEstado(self->ASM, MENU);
            break;
        default:
            return FALSE;
    }
    return TRUE;
}
