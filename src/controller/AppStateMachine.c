#include "AppStateMachine.h"
#include "gameController.h"
#include "../views/gameView.h"
#include "../views/MenuView.h"
#include "menuController.h"
#include "../views/encerramentoView.h"

void mudarEstado(struct AppStateMachine *self, AppState newState) {
    if (self->estado == newState) {
        clear();
        return;
    }

    // Executa saida de estado
    switch (newState) {
        case IN_GAME:
            leave_game(self->game);
            break;
        case MENU:
            leave_menu(self->menu);
            break;
        case ENCERRAMENTO:
        case INICIANDO:
            break;
    }
    self->estado = newState;

    // Executa a entrada do novo estado
    switch (newState) {
        case IN_GAME:
            enter_game(self->game);
            break;
        case MENU:
            enter_menu(self->menu);
            break;
        case ENCERRAMENTO:
        case INICIANDO:
            break;
    }
    // Limpa a tela quando mudar o estado.
    clear();
}

struct AppStateMachine *newASM() {
    // Aloca o espaço na memória da ASM
    struct AppStateMachine *novaASM = malloc(sizeof(struct AppStateMachine));
    novaASM->estado = INICIANDO;
    novaASM->executar = true;
    novaASM->menu = newMenu(novaASM);
    novaASM->game = newGame(novaASM);
    novaASM->encerramento = newEncerramento(novaASM);
    clear();
    return novaASM;
}

void ASM_draw(struct AppStateMachine *self) {
    if (self->estado == INICIANDO) {
        mudarEstado(self, MENU);
    }

    if (self->estado == MENU) {
        drawMenu(self->menu);
        return;
    }

    if (self->estado == IN_GAME) {
        // Exibe jogo
        move(0, 0);
        game(self->game);
        return;
    }

    if (self->estado == ENCERRAMENTO) {
        // Exibe tela de enceramento
        viewEncerramento(self->encerramento);
        return;
    }
}

bool ASM_handleInput(struct AppStateMachine *self, int ch) {

    if (ch == ERR) {
        return TRUE;
    }

    switch (self->estado) {
        case MENU:
            if (handleInputMenu(self->menu, ch)) return TRUE;
            break;
        case IN_GAME:
            if (handleInputGame(self->game, ch)) return TRUE;
            break;
        case ENCERRAMENTO:
            if (handleInputEncerramento(self->encerramento, ch)) return TRUE;
            break;
        case INICIANDO:
            break;
    }

    // Se a tecla Esc for pressionado, encerra a execução.
    if (ch == KEY_ESC) {
        self->executar = false;
        return TRUE;
    }


    // Teste da ASM
    if (ch == KEY_F(1)) {
        mudarEstado(self, MENU);
        return TRUE;
    }

    if (ch == KEY_F(2)) {
        mudarEstado(self, IN_GAME);
        return TRUE;
    }

    if (ch == KEY_F(3)) {
        mudarEstado(self, ENCERRAMENTO);
        return TRUE;
    }

    if (ch == KEY_F(5)) {
        clear();
        return TRUE;
    }


    return FALSE;
}

void ASM_update(struct AppStateMachine *self, double delta) {
    switch (self->estado) {
        case MENU:
            updateMenu(self->menu, delta);
            break;
        case IN_GAME:
            update(self->game, delta);
            break;
        case ENCERRAMENTO:
        case INICIANDO:
            break;
    }
}

void destroyASM(struct AppStateMachine *self) {
    destroyMenu(self->menu);
    self->menu = NULL;
    destroyGame(self->game);
    self->game = NULL;
    destroyEncerramento(self->encerramento);
    self->encerramento = NULL;
    free(self);
}

