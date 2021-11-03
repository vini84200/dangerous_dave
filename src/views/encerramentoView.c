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

    /*struct points aux;
    aux.points = self->ASM->game->pontuacao;
    aux.timer  = self->ASM->game->timer;

    if(goToRank(aux) == 1){
        printw("Voce esta entre os cinco melhores. Por favor, insira seu nome para participar do ranking: ");
        insertIntoRanking(aux);
    }

    char *pointer = getTextRanking();*/
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
