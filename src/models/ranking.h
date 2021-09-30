#include <stdio.h>
#include <stdlib.h>

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

struct ranking rank;

void pontuacaoSuficiente(struct points *self);

void saveRank(struct ranking *self);


