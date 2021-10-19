//
// Created by vini84200 on 27/09/2021.
//

#include "Menu.h"
#include "../controller/gameController.h"
#include "game.h"

struct Game *newGame(struct AppStateMachine *novaASM) {
    struct Game *g = malloc(sizeof(struct Game));
    // Valores padrões
    g->fase = 0;
    g->vidas = 3;
    g->pontuacao = 0;
    g->head = NULL;
    g->body = NULL;
    g->jogador = NULL;
    g->temTrofeu = false;
    g->temJetpack = false;
    g->jetpackMode = false;
    g->queda_parcial = 0.f;
    g->ASM = novaASM;
    g->animation_frame = 0;
    g->animation_frame_parcial = 0.f;
    g->pausado = false;
    g->avisoWindow = NULL;
    g->aviso = SemAviso;
    g->timer = 0.f;
    g->resultado = NAO_ENCERRADO;
    for (int i = 0; i < MAX_ENTIDADES; ++i) {
        g->entidades[i].tipo = BRANCO;
    }
    return g;
}

void destroyGame(struct Game *self) {

    free(self);
}