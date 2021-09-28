//
// Created by vini84200 on 27/09/2021.
//

#ifndef DDAVE_GAMEVIEW_H
#define DDAVE_GAMEVIEW_H

#include "../core.h"
#include "../models/Entidade.h"

#include "../controller/gameController.h"


#define CP_FUNDO    0
#define CP_PAREDE   1
#define CP_AGUA     2
#define CP_JETPACK  3
#define CP_DAVE     4
#define CP_PORTA    5
#define CP_TROFEU   6
#define CP_ENTRADA  7
#define CP_FOGO     8
#define CP_AMETISTA 9
#define CP_SAFIRA   10
#define CP_RUBI     11
#define CP_ANEL     12
#define CP_COROA    13

// Desenha um elemento do mapa à tela
void drawElement(struct _win_st *window, int elemento, int color);

// Desenha um mapa
void drawMap(struct Game *self);

// Inicia pares de cores
void init_color_pairs(struct Game *);

// Escreve na tela o header com as informações do jogo.
void header(struct Game* self);

// Funcão principal, exibe coisas na tela, e faz updates.
void game(struct Game* self);


bool handleInputGame(struct Game *self, int ch);

#endif //DDAVE_GAMEVIEW_H
