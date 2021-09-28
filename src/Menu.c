#include "Menu.h"
#include "controller/AppStateMachine.h"
#include "utils/erros.h"

struct Menu *newMenu(struct AppStateMachine *novaASM) {
    struct Menu *menu = malloc(sizeof(struct Menu));
    menu->selecionado = 0;
    menu->ASM = novaASM;
    menu->telaAberta = T_INICIAL;
    menu->janela = NULL;
    return menu;
}

void drawMenu(struct Menu *self) {
    werase(self->janela);

    int maxY = getmaxy(self->janela);
    wborder(self->janela, '|', '|', '-', '-', '+', '+', '+', '+');

    if(maxY<=MIN_Y) errorClose("Tela muito pequena!");
    int centroY = maxY / 2;
    int startMenuY = centroY - (MENU_HEIGHT/2);

    // TELA INICIAL
    if (self->telaAberta == T_INICIAL) {
        escreverTitulo(self->janela, startMenuY);
        // +3
        escreverOpcao(self->janela,"Novo Jogo", self->selecionado == NOVO_JOGO, startMenuY+3);
        escreverOpcao(self->janela,"Carregar", self->selecionado == CARREGAR, startMenuY+4);
        escreverOpcao(self->janela,"Ranking", self->selecionado == RANK, startMenuY+5);
        escreverOpcao(self->janela,"Sair", self->selecionado == SAIR, startMenuY+6);

        char txt_versao [32];
        sprintf(txt_versao, "DDave %d.%d", DDave_VERSION_MAJOR, DDave_VERSION_MINOR);
        escreverCentralizado(self->janela, txt_versao, startMenuY+8);

    }

    // TELA RANK
    if (self->telaAberta == T_RANK) {
        escreverTitulo(self->janela, 1);

        escreverCentralizado(self->janela, "RANKING de melhores jogadores", 4);

        escreverCentralizado(self->janela, "(Pressione ENTER para sair)", maxY-2);
    }


#ifdef DEBUG
    char* txt_debug [40];
    snprintf(txt_debug, 40, "Selecionado: %d | FPS: %4.3f", self->selecionado, self->fps);
    escreverCentralizado(stdscr, txt_debug, 0);
#endif
    wrefresh(self->janela);
}

void escreverCentralizado(WINDOW * w, const char *palavra, int y) {
    int x = getmaxx(stdscr);
    int centro = x/2;

    wmove(w,y, centro - strlen(palavra) / 2);
    wprintw(w, palavra);
}

void escreverTitulo(WINDOW * w, int y) {
    attron(A_BOLD);
    escreverCentralizado(w," DANGEROUS ", y);
    escreverCentralizado(w, "      DAVE ",  y+1);
    attroff(A_BOLD);
}

void escreverOpcao(WINDOW * w, char *text, bool selecionado, int y) {
    if (selecionado) {

        char *selectedLine[30] = {'\0'};
        strcat(selectedLine, "*<");
        strcat(selectedLine, text);
        strcat(selectedLine, ">* ");
        wattron(w,A_UNDERLINE | A_BOLD);
        escreverCentralizado(w, selectedLine, y);
        wattroff(w,A_UNDERLINE | A_BOLD);
    } else {
        escreverCentralizado(w, text, y);
    }
}

bool handleInputMenu(struct Menu *self, int ch) {
    if(self->telaAberta == T_INICIAL) {

        switch (ch) {
            case KEY_DOWN:
                self->selecionado++;
                if (self->selecionado >= MENU_OPCOES) self->selecionado = MENU_OPCOES - 1;
                return TRUE;
            case KEY_UP:
                self->selecionado--;
                if (self->selecionado < 0) self->selecionado = 0;
                return TRUE;
            case '\n':
                switch (self->selecionado) {
                    case NOVO_JOGO:
                        // TODO: Reiniciar o Jogo
                        ASM_mudarEstado(self->ASM, IN_GAME);
                        // Começa o jogo:
                        break;
                    case CARREGAR:
                        // COM
                        break;
                    case RANK:
                        abrirTela(self, T_RANK);
                        break;
                    case SAIR:
                        self->ASM->executar = false;
                        break;
                }

                return TRUE;
        }
    }
    else {
        if (ch == '\n'){
            fechaTela(self);
            return TRUE;
        }
        return FALSE;
    }
    return FALSE;
}

void destroyMenu(struct Menu * menu) {
    free(menu);
}

void updateMenu(struct Menu *self, double delta) {
    self->fps = (float) (1/delta);
}

void enter_menu(struct Menu * self) {
    self->janela = newwin(getmaxy(stdscr)-8, getmaxx(stdscr)-8, 4,4);
    box(self->janela, 0,0);

    wrefresh(self->janela);
}

void leave_menu(struct Menu * self) {
    wborder(self->janela, ' ', ' ', ' ',' ',' ',' ',' ',' ');
    wrefresh(self->janela);
    delwin(self->janela);
}

void abrirTela(struct Menu *self, enum MENU_TELA novaTela) {
    self->telaAberta = novaTela;
    werase(self->janela);
}

void fechaTela(struct Menu *self) {
    abrirTela(self, T_INICIAL);
}




