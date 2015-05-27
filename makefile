LIBS=`pkg-config allegro-5.0 allegro_image-5.0 allegro_font-5.0 allegro_ttf-5.0 allegro_color-5.0 allegro_primitives-5.0 --libs --cflags`

all: in9game.c in9game.h
	#compile
	gcc in9game.c -o game -Wall ${LIBS}

clear:
	rm game
