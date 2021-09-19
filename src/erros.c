#include "main.h"
#include "erros.h"

void errorClose(char* msg) {
    endwin();
    puts("ERRO CRITICO: ");
    puts(msg);
    exit(2);
}