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
                    if (a.timer > b.timer) {
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

    for (int i = 0; i < 5; i++) {
        if ((posicoes + i)->points == MIN_PTS) {
            (posicoes + i)->points = 0;
        }
    }

    FILE *pontos;
    char *path = getRankingPath();

    pontos = fopen(path, "w");

    char timers[TIMER_TEXT_CHARS * 5];
    memset(timers, 0, TIMER_TEXT_CHARS * 5);
    textSerializeTimer(primeiro.timer, timers + (TIMER_TEXT_CHARS * 0));
    textSerializeTimer(segundo.timer, timers + (TIMER_TEXT_CHARS * 1));
    textSerializeTimer(terceiro.timer, timers + (TIMER_TEXT_CHARS * 2));
    textSerializeTimer(quarto.timer, timers + (TIMER_TEXT_CHARS * 3));
    textSerializeTimer(quinto.timer, timers + (TIMER_TEXT_CHARS * 4));


    if (pontos != NULL) {
        fprintf(pontos, "%5d %-*.*s %15s\n", (posicoes + 0)->points, NOME_CHARS - 1, NOME_CHARS - 1, primeiro.name,
                timers + (TIMER_TEXT_CHARS * 0));
        fprintf(pontos, "%5d %-*.*s %15s\n", (posicoes + 1)->points, NOME_CHARS - 1, NOME_CHARS - 1, segundo.name,
                timers + (TIMER_TEXT_CHARS * 1));
        fprintf(pontos, "%5d %-*.*s %15s\n", (posicoes + 2)->points, NOME_CHARS - 1, NOME_CHARS - 1, terceiro.name,
                timers + (TIMER_TEXT_CHARS * 2));
        fprintf(pontos, "%5d %-*.*s %15s\n", (posicoes + 3)->points, NOME_CHARS - 1, NOME_CHARS - 1, quarto.name,
                timers + (TIMER_TEXT_CHARS * 3));
        fprintf(pontos, "%5d %-*.*s %15s\n", (posicoes + 4)->points, NOME_CHARS - 1, NOME_CHARS - 1, quinto.name,
                timers + (TIMER_TEXT_CHARS * 4));

        fclose(pontos);
        pontos = NULL;
    }
    free(path);
    path = NULL;
}

int goToRank(struct points self){ //Indica se um jogador pode entrar no ranking
    char pontos[NOME_CHARS] = {'0'};
    struct ranking ranking;
    int userP = self.points;
    int lastP = 0;

    ranking = getRanking();

    lastP = ranking.fifth.points;
    if (userP > lastP){
        return 1; //True
    }
    else if (userP == lastP){
        if (self.timer < ranking.fifth.timer) {
            return 1;
        } else return 0;
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
        for(int i = 0; i < 5; i++) {
            char temp[40];
            char nome[NOME_CHARS];
            memset(nome, 0, NOME_CHARS);
            int pontos;
            char timer[TIMER_TEXT_CHARS];
            memset(timer, 0, TIMER_TEXT_CHARS);

            if (fgets(temp, SER_SIZE, pontuacao) != NULL && strcmp(temp, "\n") != 0) {
                pontos = atoi(temp);

                for (int j = 0; j < SER_SIZE; j++) {
                    if (j >= 6 && j <= 25) {
                        nome[(j - 6)] = temp[j];
                    }
                    if (j >= 27 && j <= 27 + TIMER_TEXT_CHARS_S_0) {
                        timer[(j - 27)] = temp[j];
                    }
                    if (temp[j] == '\n') break;
                }
                nome[20] = '\0';
                nome[strcspn(nome, "\n")] = ' ';

            }
            else{
                pontos = MIN_PTS;
                nome[0] = '\0';
                timer[0] = '0';
                timer[1] = '\0';

            }

            memcpy((&rank.first + i)->name, &nome, NOME_CHARS);
            (&rank.first + i)->points = pontos;
            textDeserializeTimer(timer, &(&rank.first + i)->timer);
        }

        fclose(pontuacao);
        pontuacao = NULL;

        return rank;
    }
    
}

char *getTextRanking() {
    char *pontos = malloc(sizeof(char) * 5 * TEXT_RANK_SIZE);
    memset(pontos, 0, 5 * TEXT_RANK_SIZE);
    struct ranking rank = getRanking();

    for (int i = 0; i < 5; ++i) {
        struct points p = *(&rank.first + i);
        if (p.timer == 0) {
            pontos[i * TEXT_RANK_SIZE] = 0;
        } else {
            char time[30];
            getTimerText(p.timer, time);
            sprintf(pontos + i * TEXT_RANK_SIZE, "%5d - %s - %s", p.points, p.name, time);
        }
    }

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

        if ((lista + i)->points != MIN_PTS) {
            contagem++;
        }
    }
    return contagem;
}
