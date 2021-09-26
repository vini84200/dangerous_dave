#pragma once
#include "core.h"
#include "erros.h"
#include "files.h"
#include "models/Entidade.h"

#define TAMANHOY 30
#define TAMANHOX 120

struct Game {
    int fase;
    struct AppStateMachine* ASM;
    int pontuacao;
    int vidas;
    WINDOW * head;
    WINDOW * body;

    char mapa[TAMANHOY][TAMANHOX];
    struct Entidade entidades[MAX_ENTIDADES];
    struct Entidade* jogador;
    struct Vec2Int entrada;
};

struct Game* newGame(struct AppStateMachine *novaASM);

void destroyGame(struct Game* self);

// Carrega a fase e atualiza informações pertinentes
void loadFase(struct Game* self, int novaFase);

// Desenha um elemento do mapa à tela
void drawElement(WINDOW * window, char elemento, int color);

// Desenha um mapa
void drawMap(struct Game* self);

// Escreve na tela o header com as informações do jogo.
void header(struct Game* self);

// Funcão principal, exibe coisas na tela, e faz updates.
void game(struct Game* self);

// Inicia pares de cores
void init_color_pairs();

// Prepara tela para ser exibida, é chamada cada vez que o estado muda para IN_GAME
void enter_game(struct Game* self);

// Remove exibição da tela
void leave_game(struct Game* self);

bool handleInputGame(struct Game *self, int ch);

bool canMove(struct Game *self, int deltaX, int deltaY);

void movePlayer(struct Game *self, int deltaX, int deltaY);

void tryMovePlayer(struct Game *self, int deltaX, int deltaY);

// TODO GameOver
void gameOver(struct Game *self);

void morrer(struct Game *self);
