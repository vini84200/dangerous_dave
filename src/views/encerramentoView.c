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

    struct points aux;
    aux.points = self->ASM->game->pontuacao;
    aux.timer = self->ASM->game->timer;
    switch (self->estado) {
        case ESTADO_INICIAL:
            if (goToRank(aux) == 1) {
                self->foi_pro_rank = 1;
                self->estado = ESTADO_PEDINDO_NOME;
            } else {
                self->estado = ESTADO_FINAL;
            }
            break;
        case ESTADO_PEDINDO_NOME:
            printw("Voce esta entre os cinco melhores. Por favor, insira seu nome para participar do ranking: \n");
            strcpy(self->nome, "VINI");
            self->estado = ESTADO_SALVANDO;
            break;
        case ESTADO_SALVANDO:
            strcpy(aux.name, self->nome);
            insertIntoRank(aux);
            self->estado = ESTADO_FINAL;
    }
    if (self->foi_pro_rank) {
        printw("\nVoce esta entre os cinco melhores. \n");
    }
    char *pointer = getTextRanking();
    printw("%s \n %s \n %s\n %s \n %s", pointer, pointer + TEXT_RANK_SIZE, pointer + 2 * TEXT_RANK_SIZE,
           pointer + 3 * TEXT_RANK_SIZE, pointer + 4 * TEXT_RANK_SIZE);
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

void enter_encerramento(struct Encerramento *self) {
    self->estado = ESTADO_INICIAL;
    self->foi_pro_rank = 0;
}