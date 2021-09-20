#pragma once
#include <ncurses.h>

void header(){
    int score = 1000;
    int level = 1;
    int lifes = 3;

    printw("SCORE: %4.d LEVEL: %2.d LIFES: %2.d", score, level, lifes);
}

void game(){
    //Cabecalho
    WINDOW * head = newwin(3, 120, 0, 0);
    refresh();
    move(1, 3);
    header();
    box(head, 0, 0);
    wrefresh(head);

    //Corpo do jogo
    WINDOW * body = newwin(30, 120, 4, 0);
    refresh();
    box(body, 0, 0);
    wrefresh(body);

}

