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
        fprintf(pontos, "%5d %20s %8lf\n", posicoes->points, primeiro.name,      primeiro.timer);
        fprintf(pontos, "%5d %20s %8lf\n", (posicoes + 1)->points, segundo.name, segundo.timer);
        fprintf(pontos, "%5d %20s %8lf\n", (posicoes + 2)->points, terceiro.name, terceiro.timer);
        fprintf(pontos, "%5d %20s %8lf\n", (posicoes + 3)->points, quarto.name,   quarto.timer);
        fprintf(pontos, "%5d %20s %8lf\n", (posicoes + 4)->points, quinto.name,  quinto.timer);

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

    FILE *pontuacao;
    pontuacao = fopen(getRankingPath(), "r");
    //pontuacao = fopen("ranking.txt", "r");

    if(pontuacao == NULL){
        errorClose("Nao foi possivel abrir o arquivo do ranking");
    }else{
        for(int i = 0; i < 5; i++){
            char temp[40];
            char nome[21];
            int pontos;
            char timer[8];

            if (fgets(temp, 40, pontuacao) != NULL && strcmp(temp, "\n") != 0){
                pontos = atoi(temp);

                for (int j = 0; j < 35; j++){
                    if (j >= 6 && j <= 25){
                        nome[(j - 6)] = temp[j];
                    }
                    if (j >= 27 && j <= 35){
                        timer[(j - 27)] = temp[j];
                    }
                }

                nome[strcspn(nome, "\n")] = ' ';

            }
            else{
                pontos = VALUE;
                nome[0] = '\0';
                timer[0] = '0';
                timer[1] = '\0';

            }

            memcpy((&rank.first + i)->name, &nome, 20);
            (&rank.first + i)->points = pontos;
            (&rank.first + i)->timer = atof(timer);
        }

        fclose(pontuacao);
        pontuacao = NULL;

        return rank;
    }
    
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
//#else
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
