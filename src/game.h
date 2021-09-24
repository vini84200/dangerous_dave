#pragma once
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

#define TAMANHOY 30
#define TAMANHOX 121

struct Game {
    int fase;
    char mapa[TAMANHOY][TAMANHOX];
    struct AppStateMachine* ASM;
    int pontuacao;
    int vidas;
    WINDOW * head;
    WINDOW * body;
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


