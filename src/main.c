#include "game.h"

int fimJogo = 0;

void fechar(){
   fimJogo = 1;
}

void main() {
    Jogo jogo;
    int mouse_press = 0;
    
    srand(time(NULL));
	init_allegro();
    set_close_button_callback(fechar);
    
    novo_jogo(&jogo);
    
	while (!key[KEY_ESC] && !fimJogo) {
          atualiza_tela(&jogo);
          if(mouse_b & 1){
             if(!mouse_press){
                 char terminado;
                 mouse_press = 1;
                 mouse_click_esquerdo(&jogo);
                 terminado = check_vencedor(&jogo);
             
                 if(terminado != ' '){
                    atualiza_tela(&jogo);
                    if(terminado == 'X'){
                       allegro_message("\n\nO Chaves venceu!");
                       jogo.personagens[0].score++;
                    }
                    else if(terminado == 'O'){
                        allegro_message("\n\nO Kiko venceu!");
                        jogo.personagens[1].score++;
                    }
                    else allegro_message("\n\nOps, deu velha!\n");
                    nova_rodada(&jogo);
                    allegro_message("Chaves %d x %d Kiko", jogo.personagens[0].score, jogo.personagens[1].score);
                }             
             }
             
          }
          else{
             mouse_press = 0;
          }
	}
	
	stop_midi();
	deinit_allegro();
    exit(0);
}
END_OF_MAIN()
