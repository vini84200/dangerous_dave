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

enum ResultadoFinal {
    NAO_ENCERRADO,
    VITORIA,
    DERROTA
};

struct Game {
    int fase;
    struct AppStateMachine *ASM;

    // Janelas

    WINDOW *head;
    WINDOW *body;

    // Dados do mapa

    char mapa[TAMANHOY][TAMANHOX];
    struct Entidade entidades[MAX_ENTIDADES];
    struct Entidade *jogador;
    struct Vec2Int entrada;

    // Dados do jogo
    bool temTrofeu;
    bool temJetpack;
    bool jetpackMode;
    int pontuacao;
    int vidas;

    enum ResultadoFinal resultado;

    // Dados que dependem do tempo

    float queda_parcial;
    float animation_frame_parcial;
    int animation_frame;
};

struct Game* newGame(struct AppStateMachine *novaASM);

void destroyGame(struct Game* self);



#endif //DDAVE_GAME_H
