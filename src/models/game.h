//
// Created by vini84200 on 27/09/2021.
//

#ifndef DDAVE_GAME_H
#define DDAVE_GAME_H

#include "../core.h"
#include "../utils/erros.h"
#include "../files.h"
#include "../models/Entidade.h"

#define TAMANHOY 30
#define TAMANHOX 120

struct Game {
    int fase;
    struct AppStateMachine* ASM;
    int pontuacao;
    int vidas;
    bool temTrofeu;
    bool temJetpack;
    bool jetpackMode;
    WINDOW * head;
    WINDOW * body;

    char mapa[TAMANHOY][TAMANHOX];
    struct Entidade entidades[MAX_ENTIDADES];
    struct Entidade* jogador;
    struct Vec2Int entrada;

    float queda_parcial;
};

struct Game* newGame(struct AppStateMachine *novaASM);

void destroyGame(struct Game* self);



#endif //DDAVE_GAME_H
