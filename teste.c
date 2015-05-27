#include <stdlib.h>
#include <stdio.h>
#include <allegro5/allegro.h>

typedef struct t_square{
	unsigned int x, y, w, h,
		pos_regular,	// posição correta para o objeto
		pos_atual;		// posição em que o objeto se encontra
	char value;
}Square;

#define STAGE_SIZE 4

Square *squares;
int moviments_count = 0, time_count = 0;

// trata parte lógica do programa
// posição dos objetos etc...
void logic();

// pinta quadrado
void paint_squares();
void paint();

// inicia variáveis e cria
// squares
void game_init();
void game_start();
void game_quit();


int window_width(){
	return 1;
}
int window_height(){
	return 1;
}

// void game_init(){
// 	// inicar squares para os seus devidos lugares
// 	int i = 0;
// 	squares = (Square *) malloc(sizeof(Square) * (STAGE_SIZE * STAGE_SIZE));
//
// 	if(squares == NULL){
// 		perror("Não há memória suficiente");
// 		exit(0);
// 	}
//
// 	int x = 0, y = 0;
// 	while(i < STAGE_SIZE * STAGE_SIZE){
//
// 		squares[i].w = window_width() / STAGE_SIZE;
// 		squares[i].h = window_height() / STAGE_SIZE;
// 		squares[i].x = x * squares[i].w;
// 		squares[i].y = y * squares[i].h;
// 		squares[i].pos_regular = i;
// 		squares[i].pos_atual = i;
//
//
// 		y = (int) i / STAGE_SIZE;
// 		x = i - (y * STAGE_SIZE);
//
// 		// test x, y
//
// 		if(i < (STAGE_SIZE * STAGE_SIZE - 1))
// 			sprintf(&squares[i].value, "%c", i + 1);
// 		else
// 			squares[i].value = '\0';
//
// 		i++;
// 	}
// 	i = 0;
// 	while(i < STAGE_SIZE * STAGE_SIZE){
// 		printf("%d ", squares[i].value);
// 		i++;
// 	}
// }

void game_quit(){
	free(squares);
}

void game_start(){
	logic();
	paint();
}

void paint(){

}


void paint_squares(){
	int i = 0;

	while(i < STAGE_SIZE * STAGE_SIZE){
		// pintar os quadrados
		int x1 = squares[i].x * squares[i].w + 1,
				y1 = squares[i].y * squares[i].h + 1,
				x2 = squares[i].x * squares[i].w + squares[i].w - 2,
				y2 = squares[i].y * squares[i].h + squares[i].h - 2;

		i++;
	}
}

void logic(){


}
