#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

#include "game.h"

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

SDL_Rect build_rect(int x, int y) {
    SDL_Rect rectangle = { x, y, SQUARE_SIZE, SQUARE_SIZE};
    return rectangle;
}

void draw_rect(SDL_Renderer* renderer, int x, int y) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_Rect rect = build_rect(x, y);
    check_sdl_error(SDL_RenderFillRect(renderer, &rect));
}

int main() {
    SDL_Window* screen;
    SDL_Renderer* renderer;

    check_sdl_error(SDL_Init(SDL_INIT_VIDEO));

    screen = SDL_CreateWindow("Conway's Game of Life", 0, 0, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    check_sdl_pointer_error(screen);

    renderer = SDL_CreateRenderer(screen, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    check_sdl_pointer_error(renderer);

    bool running = true;
    int flag = 1;

    while(running) {
	SDL_Event event;
	while(SDL_PollEvent(&event)) {
	    switch(event.type) {
		case SDL_QUIT:
		    running = false;
		    break;
	    }
	}
	
	if(flag) {
	    printf("Drawing rect\n");
	    draw_rect(renderer, WIDTH/2, HEIGHT/2);
	}
	flag ^= 1;

	// SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	// SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(screen);
    SDL_Quit();
    return EXIT_SUCCESS;
}
