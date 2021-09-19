#include "main.h"

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

    // Impede que o programa trave esperando ações
    nodelay(stdscr, TRUE);

    // Limpa a tela antes de executar
    clear();


    printw("Hello World !!! :D");

    while (executar) {
        move(0,0);

        // Pega caracteres
        int new_ch = getch();
        if (new_ch != ERR) {
            ch = new_ch;
        }

        // Se a tecla Esc for pressionado, encerra a execução.
        if(ch == KEY_ESC) {
            executar = false;
        }

        // FIXME: Remover
        //  Teste de erro critico
        if(ch== KEY_F(1)) {
            errorClose("F1 pressionado");
        }

        // Espera alguns microssegundos
        usleep(1000);

        printw("Caractere %c, escrito com %d \n", ch);
        printw("Tempo: %d", time(NULL));


        // Atualiza a tela para exibir as alterações
        refresh();
    }


    // Encerra o NCurses
    endwin();
}
