#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../core.h"
#include "../utils/erros.h"
#include "Timer.h"

#define MIN_PTS -30000
#define NOME_CHARS 21

#define SER_SIZE 44
#define TEXT_RANK_SIZE 70

struct points {
    char name[NOME_CHARS];
    int points;
    float timer;
};


struct ranking {
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

char *getTextRanking();