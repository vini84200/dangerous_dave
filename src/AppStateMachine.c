#include "AppStateMachine.h"
#include "erros.h"

void ASM_mudarEstado(struct AppStateMachine *self, AppState newState) {
    self->estado = newState;
    // Limpa a tela quando mudar o estado.
    clear();
}

struct AppStateMachine* ASM_newASM() {
    // Aloca o espaço na memória da ASM
    struct AppStateMachine* novaASM = malloc(sizeof (struct AppStateMachine));
    novaASM->estado = MENU;
    novaASM->executar = true;
    novaASM->menu  = newMenu(novaASM);

    clear();
    return novaASM;
}

void ASM_draw(struct AppStateMachine *self) {
    if (self->estado == MENU) {
        drawMenu(self->menu);
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

bool ASM_handleInput(struct AppStateMachine *self, int ch) {
    // TODO(vini84200) Usar um switch aqui.

    if ( ch == ERR ) {
        return TRUE;
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

    if(ch== KEY_F(5)) {
        clear();
        return TRUE;
    }

    switch (self->estado) {
        case MENU:
            if(handleInputMenu(self->menu, ch)) return TRUE;
            break;
        case IN_GAME:
            break;
        case ENCERRAMENTO:
            break;
    }

    return FALSE;
}

void ASM_update(struct AppStateMachine *self) {

}

void destroyASM(struct AppStateMachine * self) {
    destroyMenu(self->menu);
    self->menu = NULL;


    free(self);
}

