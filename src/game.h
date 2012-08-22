#include <allegro.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define GAME_WIDTH 640
#define GAME_HEIGHT 360
#define PATH_IMG "image/"
#define PATH_SOUND "sound/"

typedef struct PERSONAGEM_T{
   BITMAP *bmp;
   int score;
   char simbolo;
} Personagem;

typedef struct TABULEIRO_T{
   BITMAP *bmp;
   char campos[3][3];
   int x0;
   int y0;
} Tabuleiro;

typedef struct JOGO_T{
   BITMAP *background;
   BITMAP *buffer;
   Tabuleiro tabuleiro;
   Personagem personagens[2];
   MIDI* musica;
   int vez_player;
} Jogo;

void init_allegro();
void deinit_allegro();
void atualiza_tela(Jogo *j);
void novo_jogo(Jogo *j);
void mouse_click_esquerdo(Jogo *j);
char check_vencedor(Jogo *j);
void nova_rodada(Jogo *j);
