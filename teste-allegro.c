#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv){

	if(!al_init()){
		perror("Erro ao ininciar allegro func:all_init\n");
		return -1;
	}

	if(!al_init_primitives_addon()){
		perror("Erro ao tetnar inicar addon primitive func: al_init_primitives_addon\n");
		return -1;
	}

	if(!al_init_image_addon()){
		perror("Erro ao tentar carregar addon image func: al_init_image_addon\n");
		return -1;
	}


	return 1;
}
