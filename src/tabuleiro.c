#include "tabuleiro.h"

void constroi_tabuleiro(Jogo *j){
     j->tabuleiro.bmp = create_bitmap(TABULEIRO_LADO, TABULEIRO_LADO);
}

void init_tabuleiro(Jogo *j){
     int i, k;
     
     j->tabuleiro.x0 = TABULEIRO_X0;
     j->tabuleiro.y0 = TABULEIRO_Y0;
     
     for(i = 0; i < 3; i++)
        for(k = 0; k < 3; k++)
           j->tabuleiro.campos[i][k] = ' ';
}

void desenha_tabuleiro(Jogo *j){
     int i;
     
     rectfill(j->tabuleiro.bmp, 0, 0, TABULEIRO_LADO, TABULEIRO_LADO, makecol(255, 0, 255));
     for(i = 1; i < 3; i++)
        hline(j->tabuleiro.bmp, 0, i * (TABULEIRO_LADO/3), TABULEIRO_LADO, makecol(255, 255, 255));
     
     for(i = 1; i < 3; i++)
        vline(j->tabuleiro.bmp, i * (TABULEIRO_LADO/3), TABULEIRO_LADO, 0, makecol(255, 255, 255));
}

void printa_tabuleiro(Jogo *j){
     draw_sprite(j->buffer, j->tabuleiro.bmp, j->tabuleiro.x0, j->tabuleiro.y0);
}

int click_no_tabuleiro(Jogo *j, int x, int y){
    return ((x > j->tabuleiro.x0) && (x < (j->tabuleiro.x0 + TABULEIRO_LADO))) &&
           ((y > j->tabuleiro.y0) && (y < (j->tabuleiro.y0 + TABULEIRO_LADO)));
}

int descobre_linha(Jogo *j, int y){
    if(y > j->tabuleiro.y0 && y < (j->tabuleiro.y0 + TABULEIRO_LADO/3)) return 0;
    else if((y > (j->tabuleiro.y0 + TABULEIRO_LADO/3) && (y < (j->tabuleiro.y0 + 2 * TABULEIRO_LADO/3)))) return 1;
    else return 2;
}

int descobre_coluna(Jogo *j, int x){
    if(x > j->tabuleiro.x0 && x < (j->tabuleiro.x0 + TABULEIRO_LADO/3)) return 0;
    else if((x > (j->tabuleiro.x0 + TABULEIRO_LADO/3) && (x < (j->tabuleiro.x0 + 2 * TABULEIRO_LADO/3)))) return 1;
    else return 2;
}

int posicao_valida_para_jogar(Jogo *j, int *x, int *y){
    int linha = descobre_linha(j, *y);
    int coluna = descobre_coluna(j, *x);
    
    *x = coluna;
    *y = linha;
    return j->tabuleiro.campos[linha][coluna] == ' ';
}

int posicao_x_celula(Jogo *j, int coluna){
    return (TABULEIRO_LADO/3 * coluna) + 1;
}

int posicao_y_celula(Jogo *j, int linha){
    return (TABULEIRO_LADO/3 * linha) + 1;
}
