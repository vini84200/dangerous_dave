#include "AppStateMachine.h"
#include "erros.h"
#include "game.h"

void ASM_mudarEstado(AppStateMachine *self, AppState newState) {
    self->estado = newState;
    // Limpa a tela quando mudar o estado.
    clear();
}

AppStateMachine ASM_newASM() {
    AppStateMachine novaASM;
    novaASM.estado = MENU;
    novaASM.executar = true;
    clear();
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
        game();
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

    if ( ch == ERR ) {
        return FALSE;
    }

    // Se a tecla Esc for pressionado, encerra a execução.
    if(ch == KEY_ESC) {
        self->executar = false;
        return TRUE;
    }


    // Teste da ASM
    if(ch== KEY_F(1)) {
        ASM_mudarEstado(self, MENU);
        return TRUE;
    }

    if(ch== KEY_F(2)) {
        ASM_mudarEstado(self, IN_GAME);
        return TRUE;
    }

    if(ch== KEY_F(3)) {
        ASM_mudarEstado(self, ENCERRAMENTO);
        return TRUE;
    }

    return FALSE;
}

void ASM_update(AppStateMachine *self) {

}

