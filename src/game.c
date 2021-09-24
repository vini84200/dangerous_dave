#include "game.h"

void drawElement(char elemento, int color){
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

    attron(COLOR_PAIR(color));
    printw("%c", elemento);
    attroff(COLOR_PAIR(color));
}

void drawMap(){
    int i;
    int r;

    FILE *myFile;
    myFile = fopen("/home/claytonckob/Desktop/main_folder/dangerous_dave/src/fase_01.txt", "r");

    char mapa[TAMANHOY][TAMANHOX] = {' '}; //Matriz principal
    
    if (myFile == NULL){
        printf("Error Reading File\n");
        exit (0);
    }
    for(i = 0; i < TAMANHOY; i++){
        fgets(mapa[i], TAMANHOX, myFile);
    }

	for (i = 0; i < TAMANHOY; i++) {
		for (r = 0; r < TAMANHOX; r++) {
            int posy = 4;
            int posx = 1;
            move(posy + i, posx + r);
			switch(mapa[i][r]) {
				case 'x':   drawElement(' ',  1);  break;
                case 'A':   drawElement('A',  2);  break;
                case 'J':   drawElement('H',  3);  break;
                case 'D':   drawElement('D',  4);  break;
                case 'P':   drawElement('P',  5);  break;
                case 'T':   drawElement('T',  6);  break;
                case 'O':   drawElement('O',  7);  break;
                case 'F':   drawElement('F',  8);  break;
                case '!':   drawElement('!',  4);  break;
                case ' ':   drawElement(' ',  0);  break;
            }
        }
    }
    
    fclose(myFile);
}

void header(){
    int score = 1000;
    int level = 1;
    int lifes = 3;

    printw("SCORE: %4.d LEVEL: %2.d LIFES: %2.d", score, level, lifes);
}

void game(){
    start_color();

    //Cabecalho
    WINDOW * head = newwin(3, 120, 0, 0);

    move(1, 3);
    header();
    //wrefresh(head);

    //Corpo do jogo
    move(4, 0);
    WINDOW * body = newwin(30, 120, 4, 0);

    if(has_colors() == FALSE){
      endwin();
      printf("Seu terminal não suporta cores.\n");
    }

    drawMap();

    wrefresh(body);
    getch();
    endwin();

}



