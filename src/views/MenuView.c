//
// Created by vini84200 on 28/09/2021.
//

#include "MenuView.h"


void drawMenu(struct Menu *self) {
    werase(self->janela);

    int maxY = getmaxy(self->janela);
    wborder(self->janela, ACS_VLINE, ACS_VLINE, ACS_HLINE, ACS_HLINE, ACS_ULCORNER, ACS_URCORNER, ACS_LLCORNER,
            ACS_LRCORNER);

    if (maxY <= MIN_Y) errorClose("Tela muito pequena!");
    int centroY = maxY / 2;
    int startMenuY = centroY - (MENU_HEIGHT / 2);

    // TELA INICIAL
    if (self->telaAberta == T_INICIAL) {
        escreverTitulo(self->janela, startMenuY);
        // +3
        escreverOpcao(self->janela, "Novo Jogo", self->selecionado == NOVO_JOGO, startMenuY + 3);
        escreverOpcao(self->janela, "Carregar", self->selecionado == CARREGAR, startMenuY + 4);
        escreverOpcao(self->janela, "Ranking", self->selecionado == RANK, startMenuY + 5);
        escreverOpcao(self->janela, "Sair", self->selecionado == SAIR, startMenuY + 6);

        char txt_versao[32];
        sprintf(txt_versao, "DDave %d.%d", DDave_VERSION_MAJOR, DDave_VERSION_MINOR);
        escreverCentralizado(self->janela, txt_versao, startMenuY + 8);

    }

    // TELA RANK
    if (self->telaAberta == T_RANK) {
        escreverTitulo(self->janela, 1);

        escreverCentralizado(self->janela, "RANKING de melhores jogadores", 4);

        char *pointer = getTextRanking();

        for (int i = 0; i < 5; i++) {
            if (i < maxY - 2) {
                escreverCentralizado(self->janela, pointer + i * TEXT_RANK_SIZE, (i + 6));
            }
        }

        escreverCentralizado(self->janela, "(Pressione ENTER para sair)", maxY - 2);
    }


#ifdef DEBUG
    char txt_debug[40];
    snprintf(txt_debug, 40, "Selecionado: %d | FPS: %4.3f", self->selecionado, self->fps);
    escreverCentralizado(stdscr, txt_debug, 0);
#endif

    wrefresh(self->janela);
}

void escreverCentralizado(struct _win_st *w, const char *palavra, int y) {
    int x = getmaxx(stdscr);
    int centro = x / 2;

    wmove(w, y, centro - strlen(palavra) / 2);
    wprintw(w, palavra);
}

void escreverTitulo(struct _win_st *w, int y) {
    attron(A_BOLD);
    escreverCentralizado(w, " DANGEROUS ", y);
    escreverCentralizado(w, "      DAVE ", y + 1);
    attroff(A_BOLD);
}

void escreverOpcao(struct _win_st *w, char *text, bool selecionado, int y) {
    if (selecionado) {

        wattron(w, A_UNDERLINE | A_BOLD);
        int x = getmaxx(stdscr);
        int centro = x / 2;
        wmove(w, y, (centro - strlen(text) / 2) - 2);
        waddch(w, ACS_DIAMOND);
        waddch(w, ' ');

        wmove(w, y, (centro + strlen(text) / 2) + 0);
        waddch(w, ' ');
        waddch(w, ' ');
        waddch(w, ACS_DIAMOND);
        wmove(w, y, centro - strlen(text) / 2);
        wprintw(w, text);

        wattroff(w, A_UNDERLINE | A_BOLD);
    } else {
        escreverCentralizado(w, text, y);
    }
}

bool handleInputMenu(struct Menu *self, int ch) {
    if (self->telaAberta == T_INICIAL) {
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
                        zeraGame(self->ASM->game);
                        mudarEstado(self->ASM, IN_GAME);
                        // Começa o jogo:
                        break;
                    case CARREGAR: {
                        bool carregadoComSucesso = loadGame(self->ASM->game);
                        if (carregadoComSucesso) {
                            mudarEstado(self->ASM, IN_GAME);
                        } else {
                            destroyGame(self->ASM->game);
                            self->ASM->game = newGame(self->ASM);
                        }
                    }
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
    } else {
        if (ch == '\n') {
            fechaTela(self);
            return TRUE;
        }
        return FALSE;
    }
    return FALSE;
}