#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../core.h"
#include "../utils/erros.h"

#define VALUE -30000

struct points {
    char name[30];
    int points;
    float timer;
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

struct ranking getRanking();

void saveRank(struct ranking self);

void addNewRank(struct points *self);

char *getRankingPath();

int numPlayers();