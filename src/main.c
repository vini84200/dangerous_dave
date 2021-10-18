#include "main.h"
#include "utils/time_utils.h"


int main() {
    struct AppStateMachine *maquinaEstados = newASM();

    setup_ncurses();

    struct timespec now;
    timespec_get(&now, TIME_UTC);
    struct timespec lastNow = now;

    while (maquinaEstados->executar) {
        executarASM(maquinaEstados, &now, &lastNow);
    }

    // Libera memória
    destroyASM(maquinaEstados);
    maquinaEstados = NULL;

    // Encerra o NCurses
    endwin();
}

// Executado dentro do loop
void executarASM(struct AppStateMachine *maquinaEstados, struct timespec *now, struct timespec *lastNow) {
    listenInput(maquinaEstados);

    clock_gettime(CLOCK_MONOTONIC, now);

    long deltaNanosec = calcDiffNanoseconds(now, lastNow);


    ASM_update(maquinaEstados, (double) deltaNanosec / (1e9));


    ASM_draw(maquinaEstados);

    // Atualiza a tela para exibir as alterações
    refresh();

    // Espera alguns microssegundos
    usleep((unsigned int) 1e6 / FPS_LIMIT);

    (*lastNow) = (*now);
}

void listenInput(struct AppStateMachine *maquinaEstados) {// Pega caracteres
    int new_ch = getch();

    ASM_handleInput(maquinaEstados, new_ch);
}

void setup_ncurses() {
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
}
