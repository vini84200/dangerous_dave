#include <models/Timer.h>
#include "gameView.h"

void drawElement(struct _win_st *window, int elemento, int color) {
    waddch(window, elemento | COLOR_PAIR(color));

}

void drawMap(struct Game *self) {
    init_color_pairs(self);
    int posy = 4;
    int posx = 1;
    wmove(self->body, 4, 0);
    werase(self->body);
    for (int i = 0; i < TAMANHOY; i++) {
        for (int r = 0; r < TAMANHOX; r++) {

            wmove(self->body, posy + i, posx + r);
            switch (self->mapa[i][r]) {
                case 'X':
                    drawElement(self->body, ACS_CKBOARD, CP_PAREDE);
                    break;
                case 'A':
                    drawElement(self->body, ACS_CKBOARD, CP_AGUA);
                    break;
                case 'P':
                    drawElement(self->body, ACS_BLOCK, CP_PORTA);
                    break;
                case 'O':
                    drawElement(self->body, ACS_RARROW, CP_ENTRADA);
                    break;
                case 'F':
                    drawElement(self->body, ACS_BOARD, CP_FOGO);
                    break;
                case ' ':
                    drawElement(self->body, ' ', CP_FUNDO);
                    break;
            }
        }
    }

    for (int i = 0; i < MAX_ENTIDADES; ++i) {
        if (self->entidades[i].tipo == BRANCO) break;
        wmove(self->body, posy + self->entidades[i].pos.y, posx + self->entidades[i].pos.x);
        if (!self->entidades[i].ativo) continue;
        switch (self->entidades[i].tipo) {
            case JETPACK:
                drawElement(self->body, 'H', CP_JETPACK);
                break;
            case JOGADOR:
                drawElement(self->body, ACS_TTEE, CP_DAVE);
                break;
            case TROFEU:
                drawElement(self->body, ACS_PI, CP_TROFEU);
                break;
            case AMETISTA:
                drawElement(self->body, ACS_DIAMOND, CP_AMETISTA);
                break;
            case SAFIRA:
                drawElement(self->body, ACS_DIAMOND, CP_SAFIRA);
                break;
            case RUBI:
                drawElement(self->body, ACS_DIAMOND, CP_RUBI);
                break;
            case ANEL:
                drawElement(self->body, ACS_DIAMOND, CP_ANEL);
                break;
            case COROA:
                drawElement(self->body, ACS_DIAMOND, CP_COROA);
                break;
        }
    }
    wnoutrefresh(self->body);
}


void init_color_pairs(struct Game *self) {
    if (can_change_color()) {

    }

    init_pair(CP_FUNDO, COLOR_BLACK, COLOR_BLACK);
    init_pair(CP_PAREDE, COLOR_YELLOW, COLOR_RED);
    init_pair(CP_AGUA, COLOR_WHITE, COLOR_BLUE);
    init_pair(CP_JETPACK, COLOR_BLACK, COLOR_GREEN);
    init_pair(CP_DAVE, COLOR_BLACK, COLOR_WHITE);
    init_pair(CP_PORTA, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(CP_TROFEU, COLOR_YELLOW, COLOR_BLACK);
    init_pair(CP_ENTRADA, COLOR_WHITE, COLOR_BLACK);

    init_pair(CP_AMETISTA, COLOR_CYAN, COLOR_BLACK);
    init_pair(CP_SAFIRA, COLOR_BLUE, COLOR_BLACK);
    init_pair(CP_RUBI, COLOR_GREEN, COLOR_BLACK);
    init_pair(CP_ANEL, COLOR_RED, COLOR_BLACK);
    init_pair(CP_COROA, COLOR_MAGENTA, COLOR_BLACK);

    // CORES ANIMADAS
    if (self->animation_frame % 2 == 1) {
        init_pair(CP_FOGO, COLOR_RED, COLOR_YELLOW);
    } else {
        init_pair(CP_FOGO, COLOR_YELLOW, COLOR_RED);
    }
}

void header(struct Game *self) {
    char timer[TIMER_TEXT_CHARS];
    getTimerText(self->timer, timer);
    werase(self->head);
    wmove(self->head, 0, 3);
    if (self->temJetpack) {
        if (self->temTrofeu) {
            wprintw(self->head, "%s - \t SCORE: %04d \t\t LEVEL: %01d \t\t LIFES: %01d \t\t JETPACK \t\t TROFEU",
                    timer, self->pontuacao, self->fase, self->vidas);
        } else {
            wprintw(self->head, "%s - \t SCORE: %04d \t\t LEVEL: %01d \t\t LIFES: %01d \t\t JETPACK", timer,
                    self->pontuacao,
                    self->fase, self->vidas);
        }
    } else {
        if (self->temTrofeu) {
            wprintw(self->head, "%s - \t SCORE: %04d \t\t LEVEL: %01d \t\t LIFES: %01d \t\t TROFEU", timer,
                    self->pontuacao,
                    self->fase, self->vidas);
        } else {
            wprintw(self->head, "%s - \t SCORE: %04d \t\t LEVEL: %01d \t\t LIFES: %01d ", timer, self->pontuacao,
                    self->fase,
                    self->vidas);
        }
    }
    wnoutrefresh(self->head);
}

void game(struct Game *self) {
    //Cabecalho
    header(self);

    //Corpo do jogo

    drawMap(self);

    if (self->aviso != SemAviso) {
        drawAviso(self);
    }

    doupdate();
}

bool handleInputGame(struct Game *self, int ch) {
    switch (ch) {
        case KEY_UP:
            // TODO Mover condi????o para o controller
            if (self->jetpackMode) {
                tryMovePlayer(self, 0, -1);
            } else {
                saltar(self);
            }
            break;

        case KEY_DOWN:
            tryMovePlayer(self, 0, 1);
            break;

        case KEY_LEFT:
            tryMovePlayer(self, -1, 0);
            break;

        case KEY_RIGHT:
            tryMovePlayer(self, 1, 0);
            break;

        case ' ':
            // TODO Realizar verifica????o em outro lugar
            if (self->temJetpack) {
                self->jetpackMode = !self->jetpackMode;
            }
            break;
        case KEY_ESC:
            if (self->aviso != SemAviso) {
                fechaAviso(self);
                break;
            }
            // Sai do jogo
            self->pausado = true;
            self->aviso = ConfirmaSair;
            break;
        case 'n':
            self->pausado = true;
            self->aviso = ConfirmaNovoJogo;
            break;
        case '\n':
            if (self->aviso != SemAviso) {
                confirmaAviso(self);
                return true;
            }
            return false;
        case 's':
            saveGame(self);
            return true;
        default:
            return FALSE;
    }
    return TRUE;
}

#define AVISO_WINDOW_HEIGHT 7
#define AVISO_WINDOW_LENGTH 50

void drawAviso(struct Game *self) {
    if (self->avisoWindow == NULL) {
        self->avisoWindow = newwin(AVISO_WINDOW_HEIGHT, AVISO_WINDOW_LENGTH,
                                   (getmaxy(stdscr) - AVISO_WINDOW_HEIGHT) / 2,
                                   (getmaxx(stdscr) - AVISO_WINDOW_LENGTH) / 2);

    }
    werase(self->avisoWindow);
    wborder(self->avisoWindow, ACS_VLINE, ACS_VLINE, ACS_HLINE, ACS_HLINE, ACS_ULCORNER, ACS_URCORNER, ACS_LLCORNER,
            ACS_LRCORNER);

    if (self->aviso == ConfirmaNovoJogo) {
        wmove(self->avisoWindow, 1, 2);
        wprintw(self->avisoWindow, "Recome??ar o jogo?");
        wmove(self->avisoWindow, 3, 2);
        wprintw(self->avisoWindow, "[ENTER] Confirmar");
        wmove(self->avisoWindow, 4, 2);
        wprintw(self->avisoWindow, "[ESC] Voltar");
    }

    if (self->aviso == ConfirmaSair) {
        wmove(self->avisoWindow, 1, 2);
        wprintw(self->avisoWindow, "Sair do jogo?");
        wmove(self->avisoWindow, 3, 2);
        wprintw(self->avisoWindow, "[ENTER] Confirmar");
        wmove(self->avisoWindow, 4, 2);
        wprintw(self->avisoWindow, "[ESC] Voltar");
    }

    wnoutrefresh(self->avisoWindow);
}

void confirmaAviso(struct Game *self) {
    if (self->aviso == ConfirmaSair) {
        self->ASM->executar = false;

    }
    if (self->aviso == ConfirmaNovoJogo) {
        zeraGame(self);
    }

    fechaAviso(self);
}

void fechaAviso(struct Game *self) {
    self->aviso = SemAviso;
    self->pausado = false;
    werase(self->avisoWindow);
    wborder(self->avisoWindow, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
    wnoutrefresh(self->avisoWindow);
    delwin(self->avisoWindow);
    self->avisoWindow = NULL;
}

