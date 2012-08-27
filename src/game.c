#include "game.h"

char* erros(int error_number){
     switch(error_number){
        case 1: return "Erro #01: imagem de fundo não encontrada";
        case 2: return "Erro #02: problema ao criar BITMAP para double buffering";
        case 3: return "Erro #03: a música não foi carregada";
        default: return "Erro não registrado";
     }
}

void init_allegro(){
	int depth, res;
	allegro_init();
	depth = desktop_color_depth();
	if (depth == 0) depth = 32;
	set_color_depth(depth);
	res = set_gfx_mode(GFX_AUTODETECT_WINDOWED, GAME_WIDTH, GAME_HEIGHT, 0, 0);
	if (res != 0) {
		allegro_message(allegro_error);
		exit(-1);
	}

	install_timer();
	install_keyboard();
	install_mouse();
	install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, NULL);

	show_os_cursor(MOUSE_CURSOR_ARROW);
	select_mouse_cursor(MOUSE_CURSOR_ARROW);
}

void deinit_allegro() {
	clear_keybuf();
	/* add other deinitializations here */
}

void erro_fatal(int num){
     allegro_message(erros(num));
     exit(1);
}

void atualiza_tela(Jogo *j){
     draw_sprite(screen, j->buffer, 0, 0);
}

void carregar_musica(Jogo *j){
     char faixa_str[3];
     int faixa_num = rand()%12 + 1;
     char caminho_musica[50] = PATH_SOUND;
     
     strcat(caminho_musica, "ch");
     itoa(faixa_num, faixa_str, 10);
     strcat(caminho_musica, faixa_str);
     strcat(caminho_musica, ".mid");
     
     j->musica = load_midi(caminho_musica);
     if(!(j->musica)) erro_fatal(3);
}

void constroi_jogo(Jogo *j){
     j->buffer = create_bitmap(GAME_WIDTH, GAME_HEIGHT);
     j->background = create_bitmap(GAME_WIDTH, GAME_HEIGHT);
     
     char caminho_background[50] = PATH_IMG;
     strcat(caminho_background, "background.bmp");
     j->background = load_bitmap(caminho_background, NULL);
     
     if(!(j->background)) erro_fatal(1);
     if(!(j->buffer)) erro_fatal(2);
     
     carregar_musica(j);
     constroi_tabuleiro(j);
     constroi_personagem(j);
}

void init_jogo(Jogo *j, int isReset){
     play_midi(j->musica, 1);
     j->vez_player = 0;
     init_tabuleiro(j);
     init_personagem(j, isReset);
}

void desenha_jogo(Jogo *j){
     desenha_tabuleiro(j);
}

void printa_jogo(Jogo *j){
     draw_sprite(j->buffer, j->background, 0, 0);
     printa_tabuleiro(j);
     printa_vez_atual(j);
}

void novo_jogo(Jogo *j){
     constroi_jogo(j);
     init_jogo(j, 1);
     desenha_jogo(j);
     printa_jogo(j);
}

void define_quem_comeca(Jogo *j){
     if(j->personagens[0].score <= j->personagens[1].score){
        j->vez_player = 0;
     }
     else{
        j->vez_player = 1;
     }
}

void nova_rodada(Jogo *j){
     carregar_musica(j);
     init_jogo(j, 0);
     define_quem_comeca(j);
     desenha_jogo(j);
     printa_jogo(j);
}

int deu_velha(Jogo *jogo){
    int i, j;
    
    for(i = 0; i < 3; i++)
       for(j = 0; j < 3; j++)
             if(jogo->tabuleiro.campos[i][j] == ' ') return 0;
             
    return 1;
}

char check_vencedor(Jogo *j){
     int i;
     
     for(i = 0; i < 3; i++)
        if( (j->tabuleiro.campos[i][0] == j->tabuleiro.campos[i][1]) && (j->tabuleiro.campos[i][0] == j->tabuleiro.campos[i][2]) && (j->tabuleiro.campos[i][0] != ' '))
           return j->tabuleiro.campos[i][0];
           
     for(i = 0; i < 3; i++)
        if( (j->tabuleiro.campos[0][i] == j->tabuleiro.campos[1][i]) && (j->tabuleiro.campos[0][i] == j->tabuleiro.campos[2][i]) && (j->tabuleiro.campos[0][i] != ' '))
           return j->tabuleiro.campos[0][i];
           
     if( (j->tabuleiro.campos[0][0] == j->tabuleiro.campos[2][2]) && (j->tabuleiro.campos[1][1] == j->tabuleiro.campos[2][2]) && (j->tabuleiro.campos[1][1] != ' '))
        return j->tabuleiro.campos[1][1];
     if( (j->tabuleiro.campos[1][1] == j->tabuleiro.campos[0][2]) && (j->tabuleiro.campos[1][1] == j->tabuleiro.campos[2][0]) && (j->tabuleiro.campos[1][1] != ' '))
        return j->tabuleiro.campos[1][1];
     
     if(deu_velha(j)) return 'V';
     
     return ' ';
}

void muda_vez(Jogo *j){
     j->vez_player = !j->vez_player;
     printa_vez_atual(j);
}

void jogar(Jogo *j, int coluna, int linha){
     int pos_x, pos_y;
     
     pos_x = posicao_x_celula(j, coluna);
     pos_y = posicao_y_celula(j, linha);
     
     j->tabuleiro.campos[linha][coluna] = j->personagens[j->vez_player].simbolo;
     printa_personagem(j, pos_x, pos_y);
     printa_tabuleiro(j);
}

void mouse_click_esquerdo(Jogo *j){
     static int ultimo_x = 0, ultimo_y = 0;
     int x = mouse_x, y = mouse_y;
     
     if(ultimo_x != x && ultimo_y != y){
        ultimo_x = mouse_x;
        ultimo_y = mouse_y;
        
        if(click_no_tabuleiro(j, x, y)){
           if(posicao_valida_para_jogar(j, &x, &y)){
              jogar(j, x, y);
              muda_vez(j);
           }
        }
        /*else if(click_no_reset(x, y)){
             começar um novo jogo
        }*/
     }
}
