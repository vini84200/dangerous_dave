#include "ranking.h"

void pontuacaoSuficiente(struct points *self){
    struct points joao = {"Joao", 850};
    struct points melissa = {"Melissa", 750};
    struct points alisson = {"Alisson", 650};
    struct points peter = {"Peter", 550};
    struct points pedro = {"Pedro", 450};
    struct points clayton = {"Clayton", 1000};
    struct points bro = {"Bro", 700};
    struct ranking rank = {&joao, &melissa, &alisson, &peter, &pedro};

    struct points *primeiro = rank.first;
    struct points *segundo = rank.second;
    struct points *terceiro = rank.third;
    struct points *quarto = rank.fourth;
    struct points *quinto = rank.fifth;

    //FIXME
    if (self->points > primeiro->points) {
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


void saveRank(struct ranking *self) {
    struct points *primeiro = self->first;
    struct points *segundo = self->second;
    struct points *terceiro = self->third;
    struct points *quarto = self->fourth;
    struct points *quinto = self->fifth;

    FILE *pontos;
    char *path = malloc(300);


#ifdef LINUX
    snprintf(path, 300, SAVE_FOLDER "ranking.txt", getenv("HOME"));
    char *cmd = malloc(300);
    snprintf(cmd, 300, "mkdir -p "SAVE_FOLDER, getenv("HOME"));
    system(cmd);
    snprintf(cmd, 300, "touch %s", path);
    system(cmd);
    free(cmd);
    cmd = NULL;
#else
    //FIXME: adicionar suporte para criar pasta no windows e outros
#error APENAS LINUX SUPORTADO por agora
#endif

    pontos = fopen(path, "w");

    if (pontos != NULL) {
        fprintf(pontos, "%5d %s\n", primeiro->points, primeiro->name);
        fprintf(pontos, "%5d %s\n", segundo->points, segundo->name);
        fprintf(pontos, "%5d %s\n", terceiro->points, terceiro->name);
        fprintf(pontos, "%5d %s\n", quarto->points, quarto->name);
        fprintf(pontos, "%5d %s\n", quinto->points, quinto->name);

        fclose(pontos);
        pontos = NULL;
    }
    free(path);
    path = NULL;
}

int goToRank(struct points *self){//Indica se um jogador pode entrar no ranking
    char pontos[21] = {'0'};
    int userP = self->points;
    int lastP = 0;

    FILE *pontuacao;
    pontuacao = fopen("ranking.txt", "r");

    for(int i = 0; i < 5; i++){
        if(i == 4){
            fgets(pontos, 6, pontuacao);
        }
        else{
            fgets(pontos, 20, pontuacao);
        }
    }
    lastP = atoi(pontos);
    if(userP > lastP){
        return 1; //True
    }else{
        return 0; //False
    }
    fclose(pontuacao);
    pontuacao = NULL;
}
