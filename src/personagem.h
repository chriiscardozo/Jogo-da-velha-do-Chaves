#ifndef PERSONAGEM_H        
        #define PERSONAGEM_H
        #include "game.h"

        #define NOME_P1 "Chaves"
        #define NOME_P2 "Kiko"
        #define IMG_PLAYER_1 "p1.bmp"
        #define IMG_PLAYER_2 "p2.bmp"
        #define POS_X_VEZ 10
        #define POS_Y_VEZ 250
        
        void constroi_personagem(Jogo *j);
        void init_personagem(Jogo *j, int isReset);
        void printa_personagem(Jogo *j, int pos_x, int pos_y);
        void printa_vez_atual(Jogo *j);
#endif
