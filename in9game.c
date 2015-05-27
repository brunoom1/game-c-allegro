#include "in9game.h"

ALLEGRO_EVENT_QUEUE *fila_eventos = NULL;
ALLEGRO_DISPLAY *janela = NULL;


int main(int argc, char **argv){

	int running = 1;

	if(!al_init()){
		perror("Erro ao tentar inicializar allegro");
		return -1;
	}

	if(!al_init_image_addon()){
		perror("Erro não foi possível iniciar o recurso de imagens");
		return -1;
	}

	if(!al_init_primitives_addon()){
		perror("Erro, não foi possível iniciar os recursos primitivos");
		return -1;
	}

	if(!al_install_mouse()){
		perror("Não foi possível instalar o mouse para o jogo");
		return -1;
	}

	// iniciando fonte
	al_init_font_addon();

	if(!al_init_ttf_addon()){
		perror("Erro ao tentar iniciar fonte.");
		return -1;
	}

	janela = al_create_display(WIN_W, WIN_H);
	if(!janela){
		perror("Erro ao tentar criar janela.");
		return -1;
	}

	fila_eventos = al_create_event_queue();
	if(!fila_eventos){
		al_destroy_display(janela);
		perror("Não foi possível criar lista de eventos");
		return -1;
	}

	if(!al_install_keyboard()){
		al_destroy_display(janela);
		perror("Não foi possível carregar teclado");
		return -1;
	}



	/* registrar eventos da janela */
	al_register_event_source(fila_eventos,
		al_get_display_event_source(janela)); /* add event listener */

	/*registrar eventos do teclado */
	al_register_event_source(fila_eventos,
		al_get_keyboard_event_source());

	/* registrar eventos do mouse */
	al_register_event_source(fila_eventos,
		al_get_mouse_event_source());

	/* alterar cor do clear */
	al_clear_to_color(al_map_rgb(255,255,255));
	al_flip_display();

	// carregada informações agora vamos iniciar o jogo
	// na inicialização do jogo será criado um menu, que inicialmente terá
	// só o comando para iniciar o jogo

	// inicia chamada do jogo com a logo da empresa
	game_apresentacao();

	// cria o jogo
	game_init();

	while(running){
		ALLEGRO_EVENT evento;
		al_wait_for_event(fila_eventos, &evento);

		if(fila_eventos != NULL && evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
			running = 0;
		}else	if(fila_eventos != NULL && evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
			mouse_down_event(&evento);
		}else 	if(fila_eventos != NULL && evento.type == ALLEGRO_EVENT_MOUSE_AXES){
			mouse_move_event(&evento);
		}

		// loop
		loop();

		// paint
		paint();

		// atualizar janela;
		al_flip_display();
	}

	al_shutdown_primitives_addon();
	al_destroy_event_queue(fila_eventos);
	al_destroy_display(janela);

	return 0;
}

void mouse_move_event(const ALLEGRO_EVENT *event){
	ALLEGRO_MOUSE_STATE state;
	al_get_mouse_state(&state);

	// verificar se algum dos quadrados estão na posição do mouse
	int i = 0;
	while(i < STAGE_SIZE * STAGE_SIZE){
		square_event_mouse_move(state.x, state.y, &squares[i]);
		i++;
	}
}

void mouse_down_event(const ALLEGRO_EVENT *event){
	ALLEGRO_MOUSE_STATE state;
	al_get_mouse_state(&state);
	// verificar se algum dos quadrados estão na posição do mouse
	int i = 0;
	while(i < STAGE_SIZE * STAGE_SIZE){
		square_event_mouse_down(state.x, state.y, &squares[i]);
		i++;
	}
}

void square_event_mouse_down(int x, int y, Square *square){
	if(square_mouse_pos(x, y, square)){
		square->status_mouse_down = true;
	}
	else{
		square->status_mouse_down = false;
	}
}


void square_event_mouse_move(int x, int y, Square *square){

	if(square_mouse_pos(x, y, square)){
		square->status_mouse_over = true;
	}
	else if(square->status_mouse_over){
		square->status_mouse_over = false;
		square->status_mouse_out = true;
	}
	else{
		square->status_mouse_over = false;
		square->status_mouse_out = false;
	}

}

bool square_mouse_pos(int x, int y, Square *square){
	if((x > square->x && x < square->x + square->w) &&
		(y > square->y && y < square->y + square->h))
	{
		return true;
	}
	return false;
}


int game_apresentacao(){
	// carrega recursos da apresentação
	ALLEGRO_BITMAP *logo_in9 = al_load_bitmap("./images/in9games.png");
	int logo_w = al_get_bitmap_width(logo_in9);
	int logo_h = al_get_bitmap_height(logo_in9);

	int display_w = al_get_display_width(janela);
	int display_h = al_get_display_height(janela);

	int velocidade = 18;

	if(!logo_in9){
		perror("Não foi possível carregar a logo da empresa");
		return -1;
	}

	int logo_pos_x = display_w / 2 - logo_w / 2;
	int logo_pos_y = display_h / 2 - logo_h / 2; // center
	int y = 0;

	// imagem caminha até o cnetro da tela

	while(y < logo_pos_y){
		al_clear_to_color(al_map_rgb(255,255,255));
		al_draw_bitmap(logo_in9, logo_pos_x, y, 0);
		al_flip_display();

		y += ((y % 2 == 0 && velocidade > 0)? --velocidade: 1);
	}

	// espera dois segundos
	al_rest(2);

	al_destroy_bitmap(logo_in9);

	// mostra o texto informando para clicar para então poder iniciar
	// jogo

	fade_simples();

	return 1;
}

void fade_simples(){

	int x = 255;
	int inc = -5;

	while( x < 256){

		al_clear_to_color(al_map_rgb(x,x,x));
		al_flip_display();

		x += inc;
		if(x <= 0) inc = inc * -1;
	}
}


//
// // prepara o jogo
int game_init(){

	// inicar squares para os seus devidos lugares
	squares = (Square *) malloc(sizeof(Square) * (STAGE_SIZE * STAGE_SIZE));

	if(squares == NULL){
		perror("Não há memória suficiente");
		exit(0);
	}

	int x = 0, y = 0;
	int i = 0;
	while(i < STAGE_SIZE * STAGE_SIZE){

		// ajusta x, y para colunas
		y = (int) i / STAGE_SIZE;
		x = i - (y * STAGE_SIZE);

		squares[i].w = window_width() / STAGE_SIZE;
		squares[i].h = window_height() / STAGE_SIZE;
		squares[i].x = x * squares[i].w;
		squares[i].y = y * squares[i].h;
		squares[i].pos_regular = i;
		squares[i].pos_atual = i;
		squares[i].status_mouse_over = false;
		squares[i].status_mouse_out = false;
		squares[i].status_mouse_down = false;

		// test x, y
		if(i < (STAGE_SIZE * STAGE_SIZE - 1))
			squares[i].value = i + 1;
		else
			squares[i].value = '\0';
		i++;
	}

	return 1;
}


void paint_squares(){
	int i = 0;

	ALLEGRO_FONT *font_gothic = al_load_ttf_font("fonts/fonts-japanese-gothic.ttf", 30, 0);

	while(i < STAGE_SIZE * STAGE_SIZE){
		// pintar os quadrados
		int x1 = squares[i].x,
				y1 = squares[i].y,
				x2 = squares[i].x + squares[i].w - 2,
				y2 = squares[i].y + squares[i].h - 2;

			if(squares[i].value != '\0'){

				if(squares[i].status_mouse_down){
					al_draw_filled_rectangle(x1, y1, x2, y2, al_color_html("#a5d89c"));

				}else if(squares[i].status_mouse_over){
					// pinta quadrado
					al_draw_filled_rectangle(x1, y1, x2, y2, al_color_html("#f8ef63"));
				}
				else{
					al_draw_filled_rectangle(x1, y1, x2, y2, al_color_html("#fdfad6"));
				}


				// pinta o número do quadrado
				char text[10];
				sprintf(text, "%d", squares[i].value);
				al_draw_text(font_gothic, al_color_html("#85aedb"),
					x1 + squares[i].w / 2 - al_get_text_width(font_gothic, text) / 2,
					y1 + squares[i].h / 2 - al_get_font_line_height(font_gothic) / 2,
					0, text
				);
			}


		i++;
	}

	al_destroy_font(font_gothic);
}


void paint(){
	al_clear_to_color(al_map_rgb(255,255,255));

	paint_squares();
}

void loop(){
}

//
int window_width(){
	return al_get_display_width(janela);
}

int window_height(){
	return al_get_display_height(janela);
}
