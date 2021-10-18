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
enum TiposAvisos {
    SemAviso,
    ConfirmaNovoJogo,
    ConfirmaSair
};

struct Game {
    int fase;

    // Dados do mapa

    char mapa[TAMANHOY][TAMANHOX];
    struct Vec2Int entrada;

    // Dados do jogo
    bool pausado;

    bool temTrofeu;
    bool temJetpack;
    bool jetpackMode;
    int pontuacao;
    int vidas;

    enum ResultadoFinal resultado;
    float timer;

    struct Entidade entidades[MAX_ENTIDADES];

    // Não serializados ou salvos

    // Dados que dependem do tempo
    float queda_parcial;
    float animation_frame_parcial;
    int animation_frame;

    enum TiposAvisos aviso;

    // Ponteiros, não serializados ou salvos

    struct AppStateMachine *ASM;

    // Janelas

    WINDOW *head;
    WINDOW *body;

    struct Entidade *jogador;
    WINDOW *avisoWindow;
};

struct Game *newGame(struct AppStateMachine *novaASM);

void destroyGame(struct Game *self);


#endif //DDAVE_GAME_H
