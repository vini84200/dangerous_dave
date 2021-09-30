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


