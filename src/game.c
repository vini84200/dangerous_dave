#include "game.h"
#include "Menu.h"

void drawElement(WINDOW * window, char elemento, int color){
    wattron(window,COLOR_PAIR(color));
    wprintw(window, "%c", elemento);
    wattroff(window, COLOR_PAIR(color));
}


void drawMap(struct Game* self){
    init_color_pairs();
    int posy = 4;
    int posx = 1;
    wmove(self->body, 4, 0);
	for (int i = 0; i < TAMANHOY; i++) {
		for (int r = 0; r < TAMANHOX; r++) {

            wmove(self->body, posy + i, posx + r);
			switch(self->mapa[i][r]) {
				case 'X':   drawElement(self->body, ' ',  1);  break;
                case 'A':   drawElement(self->body, 'A',  2);  break;
                case 'P':   drawElement(self->body, 'P',  5);  break;
                case 'O':   drawElement(self->body, 'O',  7);  break;
                case 'F':   drawElement(self->body, 'F',  8);  break;
                case ' ':   drawElement(self->body, ' ',  0);  break;
            }
        }
    }
    for (int i = 0; i < MAX_ENTIDADES; ++i) {
        if (self->entidades[i].tipo == BRANCO) break;
        wmove(self->body, posy + self->entidades[i].pos.x, posx + self->entidades[i].pos.y);
        switch(self->entidades[i].tipo) {
            case JETPACK:   drawElement(self->body, 'H',  3);  break;
            case JOGADOR:   drawElement(self->body, 'D',  4);  break;
            case TROFEU:   drawElement(self->body, 'T',  6);  break;
            case AMETISTA:   drawElement(self->body, '!',  4);  break;
            case BRANCO:
                break;
            case SAFIRA:
                break;
            case RUBI:
                break;
            case ANEL:
                break;
            case COROA:
                break;
        }
    }
    wrefresh(self->body);
}

void init_color_pairs() {
    init_pair(0, COLOR_BLACK, COLOR_BLACK);      //Fundo
    init_pair(1, COLOR_YELLOW, COLOR_RED);       //Parede
    init_pair(2, COLOR_WHITE, COLOR_BLUE);       //Agua
    init_pair(3, COLOR_BLACK, COLOR_GREEN);      //Jetpack
    init_pair(4, COLOR_BLACK, COLOR_WHITE);      //Dave
    init_pair(5, COLOR_MAGENTA, COLOR_BLACK);    //Porta
    init_pair(6, COLOR_YELLOW, COLOR_BLACK);     //Trofeu
    init_pair(7, COLOR_WHITE, COLOR_BLACK);      //Entrada
    init_pair(8, COLOR_RED, COLOR_RED);          //Fogo
    init_pair(9, COLOR_CYAN, COLOR_CYAN);        //Diamante
}

void header(struct Game* self){
    wmove(self->head, 0, 3);
    wprintw(self->head, "SCORE: %4.d \t\t LEVEL: %2.d \t\t LIFES: %2.d", self->pontuacao, self->fase, self->vidas);
    wrefresh(self->head);
}

void game(struct Game *self){

    if (self->fase == 0) {
        loadFase(self, 1);
    }

    //Cabecalho
    header(self);

    //Corpo do jogo

    drawMap(self);

}

struct Game *newGame(struct AppStateMachine *novaASM) {
    struct Game* g = malloc(sizeof(struct Game));
    g->fase = 0;
    g->vidas = 3;
    g->pontuacao = 1000;
    g->head = NULL;
    g->head = NULL;
    g->jogador = NULL;
    for (int i = 0; i < MAX_ENTIDADES; ++i) {
        g->entidades[i].tipo = BRANCO;
    }
    return g;
}

void destroyGame(struct Game *self) {
    free(self);
}

void loadFase(struct Game *self, int novaFase) {
    FILE *myFile;
    myFile = fopen(PASTA_NIVEIS "/fase_01.txt", "r");


    if (myFile == NULL){
        errorClose("Erro lendo o arquivo!");
    }

    int entidadesIndex = 0;

    for(int i = 0; i < TAMANHOY; i++){
        for (int j = 0; j < TAMANHOX; j++) {
            int ch = fgetc(myFile);
            if (ch == ' ' || ch == '\n') continue;
            if (ch == 'X' || ch == 'P' || ch == 'O' || ch == 'A' || ch == 'F') {
                self->mapa[i][j] = (char) ch;
                continue;
            }
            self->entidades[entidadesIndex];
            self->entidades[entidadesIndex] = newEntidadeFromCh(i, j, (char) ch);
            if(self->entidades[entidadesIndex].tipo == JOGADOR) {
                self->jogador = &self->entidades[entidadesIndex];
            }
            entidadesIndex++;
        }
    }

    if (self->jogador == NULL) {
        errorClose("MAPA INVALIDO! Sem posição do jogador.");
    }

    fclose(myFile);
    myFile = NULL;
    self->fase = novaFase;
}

void enter_game(struct Game *self) {
    start_color();

    if(has_colors() == FALSE){
        errorClose("Seu terminal não suporta cores.");
    }

    if (self->head == NULL) {
        self->head = newwin(1, 120, 0, 0);
    }

    if (self->body == NULL) {
        self->body = newwin(30, 120, 4, 0);
    }
    wrefresh(self->head);
    wrefresh(self->body);
}

void leave_game(struct Game *self) {
    delwin(self->head);
    self->head = NULL;
    delwin(self->body);
    self->body = NULL;

    use_default_colors();
}



