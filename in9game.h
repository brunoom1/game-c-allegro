#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_primitives.h>

#include <stdlib.h>
#include <stdio.h>

#define WIN_W 800
#define WIN_H 600

#define STAGE_SIZE 4

typedef struct t_square{
	unsigned int x, y, w, h,
		pos_regular,	// posição correta para o objeto
		pos_atual;		// posição em que o objeto se encontra
	char value;

	bool status_mouse_over, status_mouse_out, status_mouse_down;
}Square;

Square *squares;
int moviments_count = 0, time_count = 0;

typedef enum {
	GAME_LOCAL_INICIO,
	GAME_LOCAL_MENU,
	GAME_LOCAL_JOGO
} GameLocal;

GameLocal game_local = 0;

void loop();
void paint();
void paint_squares();

int game_init();
void game_start();
void game_quit();
int window_width();
int window_height();

int game_apresentacao();
void game_creditos();

void fade_simples();

void mouse_move_event(const ALLEGRO_EVENT *event);
void mouse_down_event(const ALLEGRO_EVENT *event);

bool square_mouse_pos(int x, int y, Square *square);
void square_event_mouse_move(int x, int y, Square *square);
void square_event_mouse_down(int x, int y, Square *square);
