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
    g->body = NULL;
    g->jogador = NULL;
    g->temTrofeu = false;
    g->temJetpack = false;
    g->jetpackMode = false;
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
            if(ch == EOF) break;
            if (ch == ' ' || ch == '\n') continue;
            if(ch=='O') {
                self->entrada.x = j;
                self->entrada.y = i;
            }
            if (ch == 'X' || ch == 'P' || ch == 'O' || ch == 'A' || ch == 'F') {

                self->mapa[i][j] = (char) ch;
                continue;
            }
            self->entidades[entidadesIndex] = newEntidadeFromCh(j, i, (char) ch);
            if(self->entidades[entidadesIndex].tipo == JOGADOR) {
                self->jogador = &self->entidades[entidadesIndex];
            }
            entidadesIndex++;
            if(entidadesIndex >= MAX_ENTIDADES) {
                errorClose("MAPA INVÁLIDO! Excede o número máximo de entidades em cena!");
            }
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

bool handleInputGame(struct Game *self, int ch) {
    if (ch == KEY_UP) {
        // TODO Trocar por pular quando não esta com jetpack
        tryMovePlayer(self, 0, -1);
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
    return FALSE;
}

bool canMove(struct Game *self, int deltaX, int deltaY) {
    struct Vec2Int initial_pos = self->jogador->pos;
    struct Vec2Int final_pos = { initial_pos.x+deltaX, initial_pos.y+deltaY};
    // Verifica paredes
    char mapPosition = self->mapa[final_pos.y][final_pos.x];
    if (mapPosition == 'X') return false;

    // Verifica sai do mapa

    if (final_pos.x < 0
            || final_pos.x > TAMANHOX
            || final_pos.y < 0
            || final_pos.y > TAMANHOY
            )
        return false;

    return true;
}

void movePlayer(struct Game *self, int deltaX, int deltaY) {
    self->jogador->pos.x += deltaX;
    self->jogador->pos.y += deltaY;

    char mapPosition = self->mapa[self->jogador->pos.y][self->jogador->pos.x];
    if (mapPosition == 'F' || mapPosition == 'A') {
        morrer(self);
    }

    for (int i = 0; i < MAX_ENTIDADES; ++i) {
        if (self->entidades[i].tipo == BRANCO) break;
        if (self->entidades[i].tipo == JOGADOR) continue;

        if(self->entidades[i].pos.x == self->jogador->pos.x
            && self->entidades[i].pos.y == self->jogador->pos.y){
            // Colisão ocorre aqui
            onColissaoEntidade(self, &self->entidades[i]);
        }
    }
}

void tryMovePlayer(struct Game *self, int deltaX, int deltaY) {
    if (canMove(self, deltaX, deltaY)) movePlayer(self, deltaX, deltaY);
}

void morrer(struct Game *self) {
    if (self->vidas <= 0) {
        gameOver(self);
    }
    self->vidas--;
    self->pontuacao -= 500;
    self->jogador->pos.x =  self->entrada.x;
    self->jogador->pos.y =  self->entrada.y;
}

void gameOver(struct Game *self) {
    // TODO GAME OVER
    errorClose("GAME OVER! Não implementado");
}

void onColissaoEntidade(struct Game *self, struct Entidade *entidade) {
    if (!entidade->ativo) return;
    entidade->ativo = false;

    switch (entidade->tipo) {
        case TROFEU:
            self->temTrofeu = true;
            break;
        case JETPACK:
            self->temJetpack = true;
            break;
        case AMETISTA:
            self->pontuacao += 50;
            break;
        case SAFIRA:
            self->pontuacao += 100;
            break;
        case RUBI:
            self->pontuacao += 150;
            break;
        case ANEL:
            self->pontuacao += 200;
            break;
        case COROA:
            self->pontuacao += 300;
            break;
    }
}



