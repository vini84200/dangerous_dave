#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
<<<<<<< HEAD
#include <math.h>
#include "../core.h"
=======
#include "../core.h"

>>>>>>> 8a7ec5c12e69270f6f708483e4c170399381376b

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

struct ranking getRanking();

void saveRank(struct ranking self);

void addNewRank(struct points *self);

