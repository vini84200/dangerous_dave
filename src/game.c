#include "game.h"
#include "erros.h"

void drawElement(WINDOW * window, char elemento, int color){
    wattron(window,COLOR_PAIR(color));
    wprintw(window, "%c", elemento);
    wattroff(window, COLOR_PAIR(color));
}


void drawMap(struct Game* self){
    init_color_pairs();
    wmove(self->body, 4, 0);
	for (int i = 0; i < TAMANHOY; i++) {
		for (int r = 0; r < TAMANHOX; r++) {
            int posy = 4;
            int posx = 1;
            wmove(self->body, posy + i, posx + r);
			switch(self->mapa[i][r]) {
				case 'x':   drawElement(self->body, ' ',  1);  break;
                case 'A':   drawElement(self->body, 'A',  2);  break;
                case 'J':   drawElement(self->body, 'H',  3);  break;
                case 'D':   drawElement(self->body, 'D',  4);  break;
                case 'P':   drawElement(self->body, 'P',  5);  break;
                case 'T':   drawElement(self->body, 'T',  6);  break;
                case 'O':   drawElement(self->body, 'O',  7);  break;
                case 'F':   drawElement(self->body, 'F',  8);  break;
                case '!':   drawElement(self->body, '!',  4);  break;
                case ' ':   drawElement(self->body, ' ',  0);  break;
            }
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
    wprintw(self->head, "SCORE: %4.d LEVEL: %2.d LIFES: %2.d", self->pontuacao, self->fase, self->vidas);
    wmove(self->head, 1, 3);
    wrefresh(self->head);
}

void game(struct Game *self){
    start_color();

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
    return g;
}

void destroyGame(struct Game *self) {
    free(self);
}

void loadFase(struct Game *self, int novaFase) {
    FILE *myFile;
    myFile = fopen("src/fase_01.txt", "r");


    if (myFile == NULL){
        errorClose("Erro lendo o arquivo!");
    }
    for(int i = 0; i < TAMANHOY; i++){
        fgets(self->mapa[i], TAMANHOX, myFile);
    }

    fclose(myFile);
    self->fase = novaFase;
}

void enter_game(struct Game *self) {


    if(has_colors() == FALSE){
        errorClose("Seu terminal não suporta cores.");
    }

    if (self->head == NULL) {
        self->head = newwin(3, 120, 0, 0);
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
}



