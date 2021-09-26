//
// Created by vini84200 on 26/09/2021.
//
#pragma once
#include "../core.h"
#include "Vec.h"

enum TiposEntidade {
    BRANCO,
    TROFEU,
    JETPACK,
    AMETISTA,
    SAFIRA,
    RUBI,
    ANEL,
    COROA,
    JOGADOR
};

enum TiposEntidade getTipoFromCh(char);


struct Entidade {
    bool ativo;
    enum TiposEntidade tipo;
    struct Vec2Int pos;

    // Reservado ao Jogador
    bool tem_jetpack;
    bool jetpack_mode;


};



struct Entidade newEntidadeFromCh(int x, int y, char ch);
struct Entidade newEntidade(int x, int y, enum TiposEntidade tipo);

void drawEntidade(struct Entidade *self);
void onColissaoEntidade(struct Entidade* self, struct Entidade* other);
void moverEntidade(struct Entidade *self, int x, int y);
