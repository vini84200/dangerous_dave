//
// Created by vini84200 on 27/09/2021.
//

#include "gameView.h"

void drawElement(struct _win_st * window, char elemento, int color){
    wattron(window,COLOR_PAIR(color));
    wprintw(window, "%c", elemento);
    wattroff(window, COLOR_PAIR(color));
}

void drawMap(struct Game* self){
    init_color_pairs();
    int posy = 4;
    int posx = 1;
    wmove(self->body, 4, 0);
    werase(self->body);
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
        wmove(self->body, posy + self->entidades[i].pos.y, posx + self->entidades[i].pos.x);
        if (!self->entidades[i].ativo) continue;
        switch(self->entidades[i].tipo) {
            case JETPACK:   drawElement(self->body, 'H',  3);  break;
            case JOGADOR:   drawElement(self->body, 'D',  4);  break;
            case TROFEU:   drawElement(self->body, 'T',  6);  break;
            case AMETISTA:   drawElement(self->body, '!',  4);  break;
            case SAFIRA: drawElement(self->body, '@',  4);  break;
            case RUBI: drawElement(self->body, '#',  4);  break;
            case ANEL: drawElement(self->body, '$',  4);  break;
            case COROA: drawElement(self->body, '%',  4);  break;
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
    if(self->temJetpack) {
        if(self->temTrofeu) {
            wprintw(self->head, "SCORE: %04d \t\t LEVEL: %01d \t\t LIFES: %01d \t\t JETPACK \t\t TROFEU", self->pontuacao, self->fase, self->vidas);
        }else {
            wprintw(self->head, "SCORE: %04d \t\t LEVEL: %01d \t\t LIFES: %01d \t\t JETPACK", self->pontuacao, self->fase, self->vidas);
        }
    }else {
        if(self->temTrofeu) {
            wprintw(self->head, "SCORE: %04d \t\t LEVEL: %01d \t\t LIFES: %01d \t\t TROFEU", self->pontuacao, self->fase, self->vidas);
        }else {
            wprintw(self->head, "SCORE: %04d \t\t LEVEL: %01d \t\t LIFES: %01d QP: %f", self->pontuacao, self->fase, self->vidas, self->queda_parcial);
        }

    }
    wrefresh(self->head);
}

void game(struct Game *self){
    //Cabecalho
    header(self);

    //Corpo do jogo

    drawMap(self);

}

bool handleInputGame(struct Game *self, int ch) {
    if (ch == KEY_UP) {
        // TODO Mover condição para o controller
        if(self->jetpackMode) {
            tryMovePlayer(self, 0, -1);
        }
        else {
            saltar(self);
        }
        return TRUE;
    }
    if (ch == KEY_DOWN) {
        tryMovePlayer(self, 0, 1);
        return TRUE;
    }
    if (ch == KEY_LEFT) {
        tryMovePlayer(self, -1, 0);
        return TRUE;
    }
    if (ch == KEY_RIGHT) {
        tryMovePlayer(self, 1, 0);
        return TRUE;
    }

    if(ch == ' ') {
        // TODO Realizar verificação em outro lugar
        if(self->temJetpack) {
            self->jetpackMode = !self->jetpackMode;
        }
        return TRUE;
    }
    return FALSE;
}