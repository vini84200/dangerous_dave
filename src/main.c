
#include <stdio.h>
#include <ncurses.h>

int main() {
    initscr();
    printw("Hello World !!! :D");
    refresh();
    getch();
    endwin();
}