#ifndef TABULEIRO_H        
        #define TABULEIRO_H
        #include "game.h"
        
        #define TABULEIRO_LADO 300
        #define TABULEIRO_X0 170
        #define TABULEIRO_Y0 40

        void constroi_tabuleiro(Jogo *j);
        void init_tabuleiro(Jogo *j);
        void desenha_tabuleiro(Jogo *j);
        void printa_tabuleiro(Jogo *j);
        int click_no_tabuleiro(Jogo *j, int x, int y);
        int posicao_valida_para_jogar(Jogo *j, int *x, int *y);
        int posicao_x_celula(Jogo *j, int coluna);
        int posicao_y_celula(Jogo *j, int linha);
#endif
