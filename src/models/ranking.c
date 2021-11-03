#include "ranking.h"

void insertIntoRank(struct points self){

    struct ranking rank = getRanking();

    struct points primeiro = rank.first;
    struct points segundo = rank.second;
    struct points terceiro = rank.third;
    struct points quarto = rank.fourth;
    struct points quinto = rank.fifth;

    struct points vetor[6] = {primeiro, segundo, terceiro, quarto, quinto, self};

    if (goToRank(self) == 1){
        int valid = 1;

        while (valid != 0){
            valid = 0;

            for (int i = 0; i < 5; i++){
                struct points a = *(vetor + i);
                struct points b = *(vetor + (i + 1));

                if (a.points < b.points){
                    *(vetor + (i + 1)) = a;
                    *(vetor + i) = b;
                    valid++;
                }

                else if (a.points == b.points){
                    if (a.timer < b.timer)
                    {
                        *(vetor + (i + 1)) = a;
                        *(vetor + i) = b;
                        valid++;
                    }
                }
            }
        }

        struct ranking newRank = {*(vetor + 0), *(vetor + 1), *(vetor + 2), *(vetor + 3), *(vetor + 4)};

        saveRank(newRank);
    }
}

void saveRank(struct ranking self)
{
    struct points primeiro = self.first;
    struct points segundo = self.second;
    struct points terceiro = self.third;
    struct points quarto = self.fourth;
    struct points quinto = self.fifth;

    struct points posicoes[5] = {primeiro, segundo, terceiro, quarto, quinto};

    for (int i = 0; i < 5; i++){
        if ((posicoes + i)->points == VALUE){
            (posicoes + i)->points = 0;
        }
    }

    FILE *pontos;
    char *path = getRankingPath();

    pontos = fopen(path, "w");

    if (pontos != NULL){
        fprintf(pontos, "%5d %20s %8lf\n", posicoes->points, primeiro.name, primeiro.timer);
        fprintf(pontos, "%5d %20s %8lf\n", (posicoes + 1)->points, segundo.name, segundo.timer);
        fprintf(pontos, "%5d %20s %8lf\n", (posicoes + 2)->points, terceiro.name, terceiro.timer);
        fprintf(pontos, "%5d %20s %8lf\n", (posicoes + 3)->points, quarto.name, quarto.timer);
        fprintf(pontos, "%5d %20s %8lf\n", (posicoes + 4)->points, quinto.name, quinto.timer);

        fclose(pontos);
        pontos = NULL;
    }
    free(path);
    path = NULL;
}

int goToRank(struct points self){ //Indica se um jogador pode entrar no ranking
    char pontos[21] = {'0'};
    struct ranking ranking;
    int userP = self.points;
    int lastP = 0;

    ranking = getRanking();

    lastP = ranking.fifth.points;
    if (userP > lastP){
        return 1; //True
    }
    else if (userP == lastP){
        if (self.timer > ranking.fifth.timer){
            return 1;
        }
        else return 0;
    }
    else return 0;
}

struct ranking getRanking(){ //Função que retorna estrutura do tipo ranking com os dados do arquivo ranking.txt
    struct ranking rank;

    struct points pr;
    struct points se;
    struct points te;
    struct points qua;
    struct points qui;

    FILE *pontuacao;
    pontuacao = fopen(getRankingPath(), "r");

    for (int i = 0; i < 5; i++){
        char temp[20];

        if (fgets(temp, 40, pontuacao) != NULL && strcmp(temp, "\n") != 0){
            char nome[21] = {0};
            int pontos = atoi(temp);
            char timer[8] = {0};

            for (int i = 0; i < 35; i++){
                if (i >= 6 && i <= 25){
                    nome[(i - 6)] = temp[i];
                }
                if (i >= 27 && i <= 35){
                    timer[(i - 27)] = temp[i];
                }
            }
            nome[strcspn(nome, "\n")] = ' ';

            switch (i){
            case 0:
                memcpy(pr.name, &nome, 20);
                pr.points = pontos;
                pr.timer = atoi(timer);
                break;
            case 1:
                memcpy(se.name, &nome, 20);
                se.points = pontos;
                se.timer = atoi(timer);
                break;
            case 2:
                memcpy(te.name, &nome, 20);
                te.points = pontos;
                te.timer = atoi(timer);
                break;
            case 3:
                memcpy(qua.name, &nome, 20);
                qua.points = pontos;
                qua.timer = atoi(timer);
                break;
            case 4:
                memcpy(qui.name, &nome, 20);
                qui.points = pontos;
                qui.timer = atoi(timer);
                break;
            }
        }
        else{
            int pontos = VALUE;
            char nome[20] = {0};

            switch (i){
            case 0:
                memcpy(pr.name, &nome, 20);
                pr.points = pontos;
                break;
            case 1:
                memcpy(se.name, &nome, 20);
                se.points = pontos;
                break;
            case 2:
                memcpy(te.name, &nome, 20);
                te.points = pontos;
                break;
            case 3:
                memcpy(qua.name, &nome, 20);
                qua.points = pontos;
                break;
            case 4:
                memcpy(qui.name, &nome, 20);
                qui.points = pontos;
                break;
            }
        }
    }

    rank.first = pr;
    rank.second = se;
    rank.third = te;
    rank.fourth = qua;
    rank.fifth = qui;

    fclose(pontuacao);
    pontuacao = NULL;

    return rank;
}

char *getTextRanking(){
    char *pontos = malloc(sizeof(char) * 5 * 40);

    FILE *pontuacao;

    char *path = getRankingPath();

    pontuacao = fopen(path, "r");

    for (int i = 0; i < 5; i++){
        fgets((pontos + (i * 40)), 40, pontuacao);
    }

    fclose(pontuacao);
    pontuacao = NULL;

    free(path);
    path = NULL;

    return pontos;
}

char *getRankingPath(){
    char *path = malloc(300);
#ifdef LINUX
    snprintf(path, 300, SAVE_FOLDER "ranking.txt", getenv("HOME"));
#elif defined(WINDOWS)
    path = SAVE_FOLDER "ranking.txt";
#else
//#error "Sistema não suportado"
#endif
    return path;
}

int numPlayers(){
    int contagem = 0;

    struct ranking players = getRanking();

    struct points primeiro = players.first;
    struct points segundo = players.second;
    struct points terceiro = players.third;
    struct points quarto = players.fourth;
    struct points quinto = players.fifth;

    struct points lista[5] = {primeiro, segundo, terceiro, quarto, quinto};

    for (int i = 0; i < 5; i++)
    {

        if ((lista + i)->points != VALUE)
        {
            contagem++;
        }
    }
    return contagem;
}