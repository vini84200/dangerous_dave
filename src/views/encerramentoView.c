#include "encerramentoView.h"


void viewEncerramento(struct Encerramento *self) {
    char *message;

    if (self->ASM->game->resultado == VITORIA) {
        message = "PARABENS! Você venceu todas as fases!";
    }
    if (self->ASM->game->resultado == DERROTA) {
        message = "GAME OVER! Você perdeu todas as suas vidas.";
    }
    char tempo[20];
    getTimerText(self->ASM->game->timer, tempo);

    move(2, 2);
    printw(message);
    move(3, 2);
    printw("Pontuação final: %04d | Tempo total:  %s", self->ASM->game->pontuacao, tempo);


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
            if (!self->modoDeEscrita) {
                enter_modoEscrita(self);
            } else {
                move(5, 2);
                printw("Voce esta entre os cinco melhores. Por favor, insira seu nome para participar do ranking: \n");
                move(6, 4);
                printw("[%-20s] \n", self->nome);
                move(6, 5 + self->ptr_digitacao);
            }
            break;
        case ESTADO_SALVANDO:
            strcpy(aux.name, self->nome);
            insertIntoRank(aux);
            self->estado = ESTADO_FINAL;
            break;
        case ESTADO_FINAL:
            move(7, 2);
            if (self->foi_pro_rank) {
                printw("\nVoce esta entre os cinco melhores. \n");
            }
            char *pointer = getTextRanking();
            printw("%s \n %s \n %s\n %s \n %s", pointer, pointer + TEXT_RANK_SIZE, pointer + 2 * TEXT_RANK_SIZE,
                   pointer + 3 * TEXT_RANK_SIZE, pointer + 4 * TEXT_RANK_SIZE);
            break;
    }

}

bool handleInputEncerramento(struct Encerramento *self, int ch) {
    switch (ch) {
        case KEY_ESC:
            if (self->estado == ESTADO_PEDINDO_NOME) {
                leave_modoEscrita(self);
                self->foi_pro_rank = false;
                self->estado == ESTADO_FINAL;
            } else {
                mudarEstado(self->ASM, MENU);
            }
            break;
        case '\n':
            if (self->estado == ESTADO_PEDINDO_NOME) {
                leave_modoEscrita(self);
                self->estado = ESTADO_SALVANDO;
            }
        default:
            if (self->modoDeEscrita) {
                if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || ch == ' ' || (ch >= '0' && ch <= '9')) {
                    if (self->ptr_digitacao > 20) return TRUE;
                    self->nome[self->ptr_digitacao] = ch;
                    self->ptr_digitacao++;
                }
                if (ch == KEY_BACKSPACE) {
                    if (self->ptr_digitacao == 0) return TRUE;
                    self->ptr_digitacao--;
                    self->nome[self->ptr_digitacao] = '\0';
                };
            }


            return FALSE;
    }
    return TRUE;
}

void enter_encerramento(struct Encerramento *self) {
    self->estado = ESTADO_INICIAL;
    self->foi_pro_rank = 0;
}

void enter_modoEscrita(struct Encerramento *self) {
    self->modoDeEscrita = TRUE;
    curs_set(TRUE);
}

void leave_modoEscrita(struct Encerramento *self) {
    self->modoDeEscrita = FALSE;
    curs_set(FALSE);
    clear();
}
