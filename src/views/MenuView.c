//
// Created by vini84200 on 28/09/2021.
//

#include "MenuView.h"

#include "../models/ranking.h"

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
        char *path = malloc(300);
        snprintf(path, 300, SAVE_FOLDER "ranking.txt", getenv("HOME"));
        FILE *myFile;
        myFile = fopen(path, "r");

        char *ranking = malloc(30);

        for (int i = 0; i < 5; i++) {
            fgets(ranking, 30, myFile);
            ranking[strlen(ranking) - 1] = '\0';

            if (i < maxY - 2) {
                escreverCentralizado(self->janela, ranking, (i + 6));
            }
        }

        fclose(myFile);

        myFile = NULL;
        free(ranking);
        ranking = NULL;

        free(path);
        path = NULL;

        escreverCentralizado(self->janela, "(Pressione ENTER para sair)", maxY - 2);
    }


#ifdef DEBUG
    char *txt_debug[40];
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
    struct points joao = {"Joao", 850};
    struct points melissa = {"Melissa", 750};
    struct points alisson = {"Alisson", 650};
    struct points peter = {"Peter", 550};
    struct points pedro = {"Pedro", 450};
    struct points clayton = {"Clayton", 1000};
    struct points bro = {"Bro", 700};
    struct ranking __rank = {&joao, &melissa, &alisson, &peter, &pedro};
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
                        // TODO: Reiniciar o Jogo
                        ASM_mudarEstado(self->ASM, IN_GAME);
                        // Começa o jogo:
                        break;
                    case CARREGAR:


                        saveRank(&__rank);

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