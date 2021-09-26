#include "Entidade.h"


enum TiposEntidade getTipoFromCh(char ch) {
    switch (ch) {
        case 'T':
            return TROFEU;
        case 'J':
            return JETPACK;
        case '!':
            return AMETISTA;
        case '@':
            return SAFIRA;
        case '#':
            return RUBI;
        case '$':
            return ANEL;
        case '%':
            return COROA;
        case 'D':
            return JOGADOR;
        default:
            return BRANCO;
    }
}

struct Entidade newEntidade(int x, int y, enum TiposEntidade tipo) {
    struct Entidade result;
    struct Vec2Int pos = {x, y};
    result.pos = pos;
    result.ativo = true;
    result.tipo = tipo;

    return result;
}

struct Entidade newEntidadeFromCh(int x, int y, char ch) {
    return newEntidade(x, y, getTipoFromCh(ch));
}
