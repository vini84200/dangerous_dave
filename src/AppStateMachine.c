#include "AppStateMachine.h"

void ASM_mudarEstado(AppStateMachine *self, AppState newState) {
    self->estado = newState;
    clear();
}

AppStateMachine ASM_newASM() {
    clear();
    AppStateMachine novaASM;
    novaASM.estado = MENU;
    novaASM.executar = true;
    return novaASM;
}

void ASM_draw(AppStateMachine *self) {
    if (self->estado == MENU) {
        // Exibe menu
        move(0,0);
        printw("MENU");
        return;
    }

    if (self->estado == IN_GAME) {
        // Exibe jogo
        move(0,0);
        printw("JOGO");
        return;
    }

    if (self->estado == ENCERRAMENTO) {
        // Exibe tela de enceramento
        move(0,0);
        printw("ENCERRAMENTO");
        return;
    }
}

bool ASM_handleInput(AppStateMachine *self, int ch) {
    // TODO(vini84200) Usar um switch aqui.

    // Teste da ASM
    if(ch== KEY_F(1)) {
        ASM_mudarEstado(self, MENU);
    }

    if(ch== KEY_F(2)) {
        ASM_mudarEstado(self, IN_GAME);
    }

    if(ch== KEY_F(3)) {
        ASM_mudarEstado(self, ENCERRAMENTO);
    }

    // Se a tecla Esc for pressionado, encerra a execução.
    if(ch == KEY_ESC) {
        self->executar = false;
    }

    return TRUE;
}

