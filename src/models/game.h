//
// Created by vini84200 on 27/09/2021.
//

#ifndef DDAVE_GAME_H
#define DDAVE_GAME_H

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

};

struct Game* newGame(struct AppStateMachine *novaASM);

void destroyGame(struct Game* self);

#include "../core.h"
#include "../erros.h"
#include "../files.h"
#include "../models/Entidade.h"

#endif //DDAVE_GAME_H
