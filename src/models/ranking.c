#include "ranking.h"

void insertIntoRank(struct points self){

    struct ranking rank = getRanking();

    struct points primeiro = rank.first;
    struct points segundo =  rank.second;
    struct points terceiro = rank.third;
    struct points quarto =   rank.fourth;
    struct points quinto =   rank.fifth;

    struct points vetor[6] = {primeiro, segundo, terceiro, quarto, quinto, self};

    if(goToRank(self) == 1){
        int valid = 1;

        while(valid != 0){
            valid = 0;

            for(int i = 0; i < 5; i++){
                struct points a = *(vetor + i);
                struct points b = *(vetor + (i + 1));

                if(a.points < b.points){
                    *(vetor + (i + 1)) = a;
                    *(vetor + i) = b;
                    valid++;
                }
            }
        }

        struct ranking newRank = {*(vetor + 0), *(vetor + 1), *(vetor + 2), *(vetor + 3), *(vetor + 4)};
    
        saveRank(newRank);
    
    }
}


void saveRank(struct ranking self) {
    struct points primeiro = self.first;
    struct points segundo =  self.second;
    struct points terceiro = self.third;
    struct points quarto =   self.fourth;
    struct points quinto =   self.fifth;

    FILE *pontos;
    char *path = getRankingPath();

    pontos = fopen(path, "w");

    if (pontos != NULL) {
        fprintf(pontos, "%5d %s\n", primeiro.points, primeiro.name);
        fprintf(pontos, "%5d %s\n", segundo.points, segundo.name);
        fprintf(pontos, "%5d %s\n", terceiro.points, terceiro.name);
        fprintf(pontos, "%5d %s\n", quarto.points, quarto.name);
        fprintf(pontos, "%5d %s\n", quinto.points, quinto.name);

        fclose(pontos);
        pontos = NULL;
    }
    free(path);
    path = NULL;
}

int goToRank(struct points self){//Indica se um jogador pode entrar no ranking
    char pontos[21] = {'0'};
    int userP = self.points;
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

struct ranking getRanking(){ //Função que retorna estrutura do tipo ranking com os dados do arquivo ranking.txt
    struct ranking rank;

    struct points pr;
    struct points se;
    struct points te;
    struct points qua;
    struct points qui;

    FILE *pontuacao;
    pontuacao = fopen("ranking.txt", "r");

    for(int i = 0; i < 5; i++){
        char temp[20];
        fgets(temp, 20, pontuacao);
        int pontos = atoi(temp);
        char nome[20] = {' '};
        memcpy(nome,  &temp[6], (sizeof(temp) - 8));
        nome[strcspn(nome, "\n")] = '\0';

        switch (i)        {
        case 0: memcpy(pr.name,  &nome, 20); pr.points  = pontos; break;
        case 1: memcpy(se.name,  &nome, 20); se.points  = pontos; break;
        case 2: memcpy(te.name,  &nome, 20); te.points  = pontos; break;
        case 3: memcpy(qua.name, &nome, 20); qua.points = pontos; break;
        case 4: memcpy(qui.name, &nome, 20); qui.points = pontos; break;
        }
    }

    rank.first =  pr;
    rank.second = se;
    rank.third =  te;
    rank.fourth = qua;
    rank.fifth =  qui;
    
    fclose(pontuacao);
    pontuacao = NULL;

    return rank;
}

char* getTextRanking(){
    char *pontos = malloc(sizeof(char)*5*30);

    FILE *pontuacao;
    pontuacao = fopen("ranking.txt", "r");
    
    for(int i = 0; i < 5; i++){
        fgets((pontos + (i*30)), 30, pontuacao);
    }

    fclose(pontuacao);
    pontuacao = NULL;

    return pontos;
}

char *getRankingPath() {
    char *path = malloc(300);
#ifdef LINUX
    snprintf(path, 300, SAVE_FOLDER "ranking.txt", getenv("HOME"));
#else
    //FIXME: adicionar suporte para criar pasta no windows e outros
#error APENAS LINUX SUPORTADO por agora
#endif
    return path;
}

int main(){
    struct points fulano = {"fulano", 750};
    insertIntoRank(fulano);

    return 0;
}