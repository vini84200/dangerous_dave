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

    struct AppStateMachine *ASM = ASM_newASM();

    struct timespec ts;
    timespec_get(&ts, TIME_UTC);
    struct timespec last_ts = ts;
    while (ASM->executar) {
        move(0,0);

        // Pega caracteres
        int new_ch = getch();

        ASM_handleInput(ASM, new_ch);


        timespec_get(&ts, TIME_UTC);
        ASM_update(ASM, (double)(ts.tv_nsec - last_ts.tv_nsec) / (1e9)); // 1E9 = 1 * 10^9

        ASM_draw(ASM);
        // Atualiza a tela para exibir as alterações
        refresh();
        // Espera alguns microssegundos
        usleep(1e6/FPS_LIMIT);
        last_ts = ts;

    }

    // Libera memória
    destroyASM(ASM);
    ASM = NULL;

    // Encerra o NCurses
    endwin();
}
