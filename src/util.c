#include "util.h"

void desenha_linha(BITMAP *destino, int x1, int y1, int x2, int y2, int grossura, int cor){
     int i;
     
     for(i = 0; i < grossura; i++)
        line(destino, x1, y1, x2, y2, cor);
}

void desenha_quadrado(BITMAP *destino, int x1, int y1, int x2, int y2, int grossura, int cor){
     int i;
     
     for(i = 0; i < grossura; i++)
        rect(destino, x1+i, y1+i, x2-i, y2-i, cor);
}
