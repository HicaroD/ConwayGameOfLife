#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

#include "game.h"

#define SEED_ROWS 1

void check_sdl_error(int code) {
    if(code != 0) {
	fprintf(stderr, "SDL ERROR: %s", SDL_GetError());
	exit(EXIT_FAILURE);
    }
}

void check_sdl_pointer_error(void* ptr) {
    if(ptr == NULL) {
	fprintf(stderr, "Couldn't create window: %s", SDL_GetError());
	exit(EXIT_FAILURE);
    }
}

/* int** generate_random_seed() { */
/*     for(int row = 0; row < SEED_ROWS; row++) { */
/* 	int x = rand() % WIDTH; */
/* 	int y = rand() % HEIGHT; */

/* 	seed[row][0] = y; */
/* 	seed[row][1] = x; */
/*     } */

/*     return seed; */
/* } */

int main() {
    SDL_Window* screen;
    SDL_Renderer* renderer;

    check_sdl_error(SDL_Init(SDL_INIT_VIDEO));

    screen = SDL_CreateWindow("Conway's Game of Life", 0, 0, SCREEN_WIDTH, SCREEN_WIDTH, SDL_WINDOW_SHOWN);
    check_sdl_pointer_error(screen);

    renderer = SDL_CreateRenderer(screen, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    check_sdl_pointer_error(renderer);

    int seed[SEED_ROWS][2] = {{10, 10}};
    struct Game* game = new_game(SEED_ROWS, seed);
    bool running = true;

    while(running) {
	SDL_Event event;
	while(SDL_PollEvent(&event)) {
	    switch(event.type) {
		case SDL_QUIT:
		    running = false;
		    break;
	    }
	}

	// SDL_RenderClear(renderer);
	update_game_board(game);
	draw_game_board(game, renderer);
	SDL_RenderPresent(renderer);
    }

    free(game);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(screen);
    SDL_Quit();
    return EXIT_SUCCESS;
}
