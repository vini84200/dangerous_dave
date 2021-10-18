#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../core.h"


struct points {
    char name[30];
    int points;
};


struct ranking{ 
    struct points first;
    struct points second;
    struct points third;
    struct points fourth;
    struct points fifth;
};

int goToRank(struct points self);

void insertIntoRank(struct points self);



// FUNÇÕES PARA SEREM IMPLEMENTADAS:
// FUNCAO QUE RETORNA O CAMINHO DO ARQUIVO ranking.h
// Funçao que retorna um struct ranking, carregando ele da memoria. (Lembre-se que podem não haver pontuações nele)
struct ranking getRanking();
// Função que retorna um char* do ranking (Use a função à cima e converta em texto)
//char * getTextRanking();
// Função que salva um ranking na memoria
void saveRank(struct ranking self);
// Função que adiciona um rank à um ranking, na posição correta e remove o que sobrar, salvando na memoria.
void addNewRank(struct points *self);

