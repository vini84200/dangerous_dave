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
};


struct Entidade newEntidadeFromCh(int x, int y, char ch);

struct Entidade newEntidade(int x, int y, enum TiposEntidade tipo);

void drawEntidade(struct Entidade *self);

void moverEntidade(struct Entidade *self, int x, int y);
