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

    // Remove delay ao pressionar Esc.
    set_escdelay(0);

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

        clock_gettime(CLOCK_MONOTONIC, &ts);

        double ds = difftime(ts.tv_sec, last_ts.tv_sec);
        long dns = ts.tv_nsec - last_ts.tv_nsec;

        if (dns < 0) {
            ds -= 1;
            dns += 1000000000;
        }

        ASM_update(ASM, (double) dns/(1e9));

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
