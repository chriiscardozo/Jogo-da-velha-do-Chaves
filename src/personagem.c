#include "personagem.h"

void constroi_personagem(Jogo *j){
     char caminho_img_p1[50] = PATH_IMG;
     char caminho_img_p2[50] = PATH_IMG;
     
     //Player 1
     strcat(caminho_img_p1, IMG_PLAYER_1);
     j->personagens[0].bmp = create_bitmap(50, 50);
     j->personagens[0].bmp = load_bitmap(caminho_img_p1, NULL);

     //Player 2
     strcat(caminho_img_p2, IMG_PLAYER_2);
     j->personagens[1].bmp = create_bitmap(50, 50);
     j->personagens[1].bmp = load_bitmap(caminho_img_p2, NULL);
     
     if(!j->personagens[0].bmp){
        allegro_message("Nao foi possivel carregar a imagem do player 1");
        exit(1);
     }
     if(!j->personagens[1].bmp){
        allegro_message("Nao foi possivel carregar a imagem do player 2");        
        exit(1);
     }
}

void init_personagem(Jogo *j){
     j->personagens[0].score = 0;
     j->personagens[0].simbolo = 'X';
     j->personagens[1].score = 0;
     j->personagens[1].simbolo = 'O';
}

void printa_personagem(Jogo *j, int pos_x, int pos_y){
     draw_sprite(j->tabuleiro.bmp, j->personagens[j->vez_player].bmp, pos_x, pos_y);
}

void printa_vez_atual(Jogo *j){
     draw_sprite(j->buffer, j->personagens[j->vez_player].bmp, POS_X_VEZ, POS_Y_VEZ);
     
     desenha_quadrado(j->buffer, POS_X_VEZ, POS_Y_VEZ, POS_X_VEZ + 100, POS_Y_VEZ + 100, 10, makecol(255, 20, 20));
}
