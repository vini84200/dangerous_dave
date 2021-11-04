#include "gameController.h"

void loadFase(struct Game *self, int novaFase)
{
    FILE *myFile;
    char filePath[300] = {'\0'};
    snprintf(filePath, 300, PASTA_NIVEIS "/fase_%02d.txt", novaFase);
    myFile = fopen(filePath, "r");

    if (myFile == NULL)
    {
        errorClose("Erro lendo o arquivo!");
    }

    int entidadesIndex = 0;

    // Limpar mapa
    for (int x = 0; x < TAMANHOX; ++x)
    {
        for (int y = 0; y < TAMANHOY; ++y)
        {
            self->mapa[y][x] = ' ';
        }
    }
    // Limpa entidades
    for (int i = 0; i < MAX_ENTIDADES; ++i)
    {
        self->entidades[i].tipo = BRANCO;
    }

    // Tira estados especiais
    self->temJetpack = false;
    self->temTrofeu = false;
    self->jetpackMode = false;

    //Carrega mapa
    for (int i = 0; i < TAMANHOY; i++)
    {
        for (int j = 0; j < TAMANHOX; j++)
        {
            int ch = fgetc(myFile);
            if (ch == EOF)
                break;
            if (ch == ' ')
                continue;
            if (ch == '\n')
                break;
            if (ch == 'O')
            {
                self->entrada.x = j;
                self->entrada.y = i;
            }
            if (ch == 'X' || ch == 'P' || ch == 'O' || ch == 'A' || ch == 'F')
            {

                self->mapa[i][j] = (char)ch;
                continue;
            }
            self->entidades[entidadesIndex] = newEntidadeFromCh(j, i, (char)ch);
            if (self->entidades[entidadesIndex].tipo == JOGADOR)
            {
                self->jogador = &self->entidades[entidadesIndex];
            }
            entidadesIndex++;
            if (entidadesIndex >= MAX_ENTIDADES)
            {
                errorClose("MAPA INVÁLIDO! Excede o número máximo de entidades em cena!");
            }
        }
    }

    if (self->jogador == NULL)
    {
        errorClose("MAPA INVALIDO! Sem posição do jogador.");
    }

    fclose(myFile);
    myFile = NULL;
    self->fase = novaFase;
    self->temJetpack = false;
    self->temTrofeu = false;
}

void enter_game(struct Game *self)
{
    if (self->fase == 0)
        loadFase(self, 1);
    start_color();
    if (has_colors() == FALSE)
    {
        errorClose("Seu terminal não suporta cores.");
    }

    if (self->head == NULL)
    {
        self->head = newwin(1, 120, 0, 0);
    }

    if (self->body == NULL)
    {
        self->body = newwin(30, 120, 4, 0);
    }

    wrefresh(self->head);
    wrefresh(self->body);
    // Verifica que o jogo não pode ser continuado após ser encerrado.
    if (self->resultado == VITORIA)
    {
        vitoria(self);
    }
    if (self->resultado == DERROTA)
    {
        gameOver(self);
    }
}

void leave_game(struct Game *self)
{
    delwin(self->head);
    self->head = NULL;
    delwin(self->body);
    self->body = NULL;

    use_default_colors();
}

bool canMove(struct Game *self, int deltaX, int deltaY)
{
    if (self->pausado)
        return false;
    struct Vec2Int initial_pos = self->jogador->pos;
    struct Vec2Int final_pos = {initial_pos.x + deltaX, initial_pos.y + deltaY};
    // Verifica paredes
    char mapPosition = self->mapa[final_pos.y][final_pos.x];
    if (mapPosition == 'X')
        return false;

    // Verifica sai do mapa

    if (final_pos.x < 0 || final_pos.x > TAMANHOX || final_pos.y < 0 || final_pos.y > TAMANHOY)
        return false;

    return true;
}

void movePlayer(struct Game *self, int deltaX, int deltaY)
{
    self->jogador->pos.x += deltaX;
    self->jogador->pos.y += deltaY;

    char mapPosition = self->mapa[self->jogador->pos.y][self->jogador->pos.x];
    // Checa por fogo e agua, se for o jogador morre
    if (mapPosition == 'F' || mapPosition == 'A')
    {
        morrer(self);
    }

    // Checa por vitória
    if (mapPosition == 'P' && self->temTrofeu)
    {
        venceFase(self);
    }

    // Checa colisões com entidades
    for (int i = 0; i < MAX_ENTIDADES; ++i)
    {
        if (self->entidades[i].tipo == BRANCO)
            break;
        if (self->entidades[i].tipo == JOGADOR)
            continue;

        if (self->entidades[i].pos.x == self->jogador->pos.x && self->entidades[i].pos.y == self->jogador->pos.y)
        {
            // Colisão ocorre aqui
            onColissaoEntidade(self, &self->entidades[i]);
        }
    }
}

void tryMovePlayer(struct Game *self, int deltaX, int deltaY)
{
    if (canMove(self, deltaX, deltaY))
        movePlayer(self, deltaX, deltaY);
}

void morrer(struct Game *self)
{
    if (self->vidas <= 0)
    {
        gameOver(self);
    }
    self->vidas--;
    self->pontuacao -= 500;
    self->jogador->pos.x = self->entrada.x;
    self->jogador->pos.y = self->entrada.y;
}

void gameOver(struct Game *self)
{
    self->resultado = DERROTA;
    mudarEstado(self->ASM, ENCERRAMENTO);
}

void onColissaoEntidade(struct Game *self, struct Entidade *entidade)
{
    if (!entidade->ativo)
        return;
    entidade->ativo = false;

    switch (entidade->tipo)
    {
    case TROFEU:
        self->temTrofeu = true;
        break;
    case JETPACK:
        self->temJetpack = true;
        break;
    case AMETISTA:
        self->pontuacao += 50;
        break;
    case SAFIRA:
        self->pontuacao += 100;
        break;
    case RUBI:
        self->pontuacao += 150;
        break;
    case ANEL:
        self->pontuacao += 200;
        break;
    case COROA:
        self->pontuacao += 300;
        break;
    case BRANCO:
    case JOGADOR:
        errorClose("Jogador não deve colidir com Branco ou Jogador");
    }
}

void update(struct Game *self, double deltaT)
{
    if (!self->pausado)
    {
        // Gravidade
        if (!isApoiado(self))
        {

            self->queda_parcial += TAXA_QUEDA * (float)deltaT;
            if (self->queda_parcial >= 1)
            {
                self->queda_parcial = 0;
                movePlayer(self, 0, 1);
            }
        }
        else
        {
            self->queda_parcial = 0.f;
        }

        self->timer += (float)deltaT;
    }

    self->animation_frame_parcial += (float)deltaT;
    if (self->animation_frame_parcial >= DURACAO_FRAME)
    {
        self->animation_frame_parcial -= DURACAO_FRAME;
        self->animation_frame += 1;
        if (self->animation_frame >= QUANT_FRAMES)
        {
            self->animation_frame = 0;
        }
    }
}

bool isApoiado(struct Game *self)
{
    return !canMove(self, 0, 1) || self->jetpackMode;
}

void saltar(struct Game *self)
{
    if (!isApoiado(self))
        return;

    for (int i = 0; i < MAX_JUMP; ++i)
    {
        if (canMove(self, 0, -1))
            movePlayer(self, 0, -1);
        else
            break;
    }
}

void venceFase(struct Game *self)
{
    if (self->fase == QUANT_FASES)
    {
        vitoria(self);
        return;
    }
    // Avança de fase
    loadFase(self, self->fase + 1);
}

void vitoria(struct Game *self)
{
    self->resultado = VITORIA;
    mudarEstado(self->ASM, ENCERRAMENTO);
}

void zeraGame(struct Game *self)
{
    self->pontuacao = 0;
    self->vidas = 3;
    self->resultado = NAO_ENCERRADO;
    self->timer = 0;
    loadFase(self, 1);
}

char *getSavePath()
{
    char *path = malloc(300);
#ifdef LINUX
    snprintf(path, 300, SAVE_FOLDER "game_save", getenv("HOME"));
#elif defined(WINDOWS)
    path = SAVE_FOLDER "game_save";
#else
#error "Sistema não suportado!"
#endif
    return path;
}

// TPL docs:  https://troydhanson.github.io/tpl/userguide.html#format
#define SAVE_FORMAT "iiS(ic##$(ii)iiiiiiii)S(ii$(ii))#"

bool saveGame(struct Game *self)
{

    tpl_node *tn;
    int v_major = DDave_VERSION_MAJOR;
    int v_minor = DDave_VERSION_MINOR;
    tn = tpl_map(SAVE_FORMAT, &v_major, &v_minor, self, TAMANHOY, TAMANHOX, self->entidades, MAX_ENTIDADES);
    tpl_pack(tn, 0);
    int res = tpl_dump(tn, TPL_FILE, getSavePath());
    tpl_free(tn);
    return 0;
}

bool loadGame(struct Game *self)
{
    struct AppStateMachine *appStateMachine = self->ASM;
    tpl_node *tn;
    int save_version_major;
    int save_version_minor;
    tn = tpl_map(SAVE_FORMAT, &save_version_major, &save_version_minor, self, TAMANHOY, TAMANHOX, self->entidades,
                 MAX_ENTIDADES);
    int loadRes = tpl_load(tn, TPL_FILE, getSavePath());

    tpl_unpack(tn, 0);

    tpl_free(tn);
    if (loadRes == -1)
    {
        return false;
    }

    if (save_version_major != DDave_VERSION_MAJOR)
    {

        return false;
    }
    self->ASM = appStateMachine;

    for (int i = 0; i < MAX_ENTIDADES; ++i){
        if (self->entidades[i].tipo == JOGADOR)
        {
            self->jogador = &self->entidades[i];
        }
    }
    return true;
}