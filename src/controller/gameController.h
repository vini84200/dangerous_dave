#pragma once

#include "../core.h"
#include "../utils/erros.h"
#include "../files.h"
#include "../models/Entidade.h"
#include "../models/Menu.h"
#include "../models/game.h"

// Taxa de queda em blocos por segundo
#define TAXA_QUEDA 1.3f
#define DURACAO_FRAME 0.25f
#define QUANT_FRAMES 4
#define QUANT_FASES 2


// Carrega a fase e atualiza informações pertinentes
void loadFase(struct Game *self, int novaFase);

// Prepara tela para ser exibida, é chamada cada vez que o estado muda para IN_GAME
void enter_game(struct Game *self);

// Remove exibição da tela
void leave_game(struct Game* self);

void update(struct Game* self, double deltaT);

bool canMove(struct Game *self, int deltaX, int deltaY);

void movePlayer(struct Game *self, int deltaX, int deltaY);

void tryMovePlayer(struct Game *self, int deltaX, int deltaY);

// TODO GameOver
void gameOver(struct Game *self);

void morrer(struct Game *self);

void onColissaoEntidade(struct Game *self, struct Entidade *entidade);

bool isApoiado(struct Game *self);

// Jogador salta
void saltar(struct Game *self);

// Quando o jogoador passa uma fase
void venceFase(struct Game *self);

// Dado um jogo, altera suas informações para reiniciar o jogo.
void zeraGame(struct Game *self);