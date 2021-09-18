
#include <ncurses.h>
#include <unistd.h>

#include "core.h"

int main() {
    int ch;
    bool executar = true;

    // Inicializa o modo NCurses
    initscr();
    // Desabilita o buffer de caracteres(eg. permite a leitura de caracteres sem ter que esperar o enter)
    raw();
    // Impede que os caracteres pressionados apareçam na tela
    noecho();

    // Não exibe o cursor no terminal
    curs_set(FALSE);

    // Ativa o uso das teclas de setas.
    keypad(stdscr, TRUE);

    printw("Hello World !!! :D");

    while (executar) {
        // Limpa a tela antes de executar
        clear();

        // Atualiza a tela para exibir as alterações
        refresh();

        // Pega caracteres
        ch = getch();

        // Se a tecla Esc for pressionado, encerra a execução.
        if(ch == KEY_ESC) {
            executar = false;
        }

        // Esperra alguns microsegundos
        usleep(2);
        printw("Caractere %c, escrito com %d", ch);
    }


    // Encerra o NCurses
    endwin();
}