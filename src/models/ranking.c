#include "ranking.h"

struct points joao = {"Joao", 450};  
struct points melissa = {"Melissa", 650}; 
struct points alisson = {"Alisson", 850}; 
struct points peter = {"Peter", 250}; 
struct points pedro = {"Pedro", 150}; 

struct ranking rank = {&joao, &melissa, &alisson, &peter, &pedro};

struct ranking *p = &rank;

void saveRank(struct ranking *self){
    struct points *primeiro = self->first;
    struct points *segundo = self->second;
    struct points *terceiro = self->third;
    struct points *quarto = self->fourth;
    struct points *quinto = self->fifth;

    
    FILE *pontos;

    pontos = fopen("ranking.txt", "w");

    fprintf(pontos,"%5d - %s\n", primeiro->points, primeiro->name);
    fprintf(pontos,"%5d - %s\n", segundo->points, segundo->name);
    fprintf(pontos,"%5d - %s\n", terceiro->points, terceiro->name);
    fprintf(pontos,"%5d - %s\n", quarto->points, quarto->name);
    fprintf(pontos,"%5d - %s\n", quinto->points, quinto->name);
}


