#pragma once
#include <stdio.h>
#include <stdlib.h>
#include "../core.h"

struct points{
    char name[30];
    int points;
};


struct ranking{
    struct points *first;
    struct points *second;
    struct points *third;
    struct points *fourth;
    struct points *fifth;
};


void pontuacaoSuficiente(struct points *self);

void saveRank(struct ranking *self);


// FUNÇÕES PARA SEREM IMPLEMENTADAS:
// FUNCAO QUE RETORNA O CAMINHO DO ARQUIVO ranking.h
// Funçao que retorna um struct ranking, carregando ele da memoria. (Lembre-se que podem não haver pontuações nele)
// Função que retorna um char* do ranking (Use a função à cima e converta em texto)
// Função que salva um ranking na memoria
// Função que dado uma pontuacao em int e um ranking retorna se deve adicionar ele ao ranking ou não
// Função que adiciona um rank à um ranking, na posição correta e remove o que sobrar, salvando na memoria.

