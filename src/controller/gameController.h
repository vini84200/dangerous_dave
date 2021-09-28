#pragma once
#include "../core.h"
#include "../erros.h"
#include "../files.h"
#include "../models/Entidade.h"
#include "../Menu.h"
#include "../models/game.h"

// Taxa de queda em blocos por segundo
#define TAXA_QUEDA 1.3f
#define QUANT_FASES 2

// Carrega a fase e atualiza informações pertinentes
void loadFase(struct Game* self, int novaFase);

// Prepara tela para ser exibida, é chamada cada vez que o estado muda para IN_GAME
void enter_game(struct Game* self);

// Remove exibição da tela
void leave_game(struct Game* self);

void update(struct Game* self, double deltaT);

bool canMove(struct Game *self, int deltaX, int deltaY);

void movePlayer(struct Game *self, int deltaX, int deltaY);

void tryMovePlayer(struct Game *self, int deltaX, int deltaY);

// TODO GameOver
void gameOver(struct Game *self);

void morrer(struct Game *self);

void onColissaoEntidade(struct Game* self, struct Entidade* entidade);

bool isApoiado(struct Game* self);

void saltar(struct Game* self);

void venceFase(struct Game* self);