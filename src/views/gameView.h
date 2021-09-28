//
// Created by vini84200 on 27/09/2021.
//

#ifndef DDAVE_GAMEVIEW_H
#define DDAVE_GAMEVIEW_H

#include "../core.h"
#include "../models/Entidade.h"

#include "../controller/gameController.h"

// Desenha um elemento do mapa à tela
void drawElement(struct _win_st * window, char elemento, int color);

// Desenha um mapa
void drawMap(struct Game* self);

// Inicia pares de cores
void init_color_pairs();

// Escreve na tela o header com as informações do jogo.
void header(struct Game* self);

// Funcão principal, exibe coisas na tela, e faz updates.
void game(struct Game* self);


bool handleInputGame(struct Game *self, int ch);

#endif //DDAVE_GAMEVIEW_H
