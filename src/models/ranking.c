#include "ranking.h"

struct points joao = {"Joao", 850};  
struct points melissa = {"Melissa", 750}; 
struct points alisson = {"Alisson", 650}; 
struct points peter = {"Peter", 550}; 
struct points pedro = {"Pedro", 450}; 
struct points clayton = {"Clayton", 1000};
struct points bro = {"Bro", 700};

struct ranking *p = &rank;

struct points *s = &bro;

void pontuacaoSuficiente(struct points *self){
    struct ranking rank = {&joao, &melissa, &alisson, &peter, &pedro};

    struct points *primeiro = rank.first;
    struct points *segundo =  rank.second;
    struct points *terceiro = rank.third;
    struct points *quarto =   rank.fourth;
    struct points *quinto =   rank.fifth;

    //FIXME
    if(self->points > primeiro->points){
        rank.fifth =  quarto;
        rank.fourth = terceiro;
        rank.third =  segundo;
        rank.second = primeiro;
        rank.first = self;
    }
    else if(self->points > segundo->points){
        rank.fifth =  quarto;
        rank.fourth = terceiro;
        rank.third =  segundo;
        rank.second = self;
    }
    else if(self->points > terceiro->points){
        rank.fifth =  quarto;
        rank.fourth = terceiro;
        rank.third =  self;
    }
    else if(self->points > quarto->points){
        rank.fifth =  quarto;
        rank.fourth = self;
    }
    else if(self->points > quinto->points){
        rank.fifth =  self;
    }

    struct ranking *pr = &rank;
    

    saveRank(pr);




}


void saveRank(struct ranking *self){
    struct points *primeiro = self->first;
    struct points *segundo = self->second;
    struct points *terceiro = self->third;
    struct points *quarto = self->fourth;
    struct points *quinto = self->fifth;

    FILE *pontos;

    pontos = fopen("ranking.txt", "w");

    fprintf(pontos,"%5d %s\n", primeiro->points, primeiro->name);
    fprintf(pontos,"%5d %s\n", segundo->points, segundo->name);
    fprintf(pontos,"%5d %s\n", terceiro->points, terceiro->name);
    fprintf(pontos,"%5d %s\n", quarto->points, quarto->name);
    fprintf(pontos,"%5d %s\n", quinto->points, quinto->name);
}

int main(){
    pontuacaoSuficiente(s);

}
