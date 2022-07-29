#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

#define WIDTH 720
#define HEIGHT 480

void check_sdl_error(int code) {
    if(code < 0) {
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

int main() {
    check_sdl_error(SDL_Init(SDL_INIT_VIDEO));

    SDL_Window* screen = SDL_CreateWindow("Conway's Game of Life", 100, 100, WIDTH, HEIGHT, SDL_WINDOWEVENT_SHOWN);
    check_sdl_pointer_error(screen);

    SDL_Renderer* renderer = SDL_CreateRenderer(screen, -1, SDL_RENDERER_ACCELERATED);
    check_sdl_pointer_error(renderer);
    
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(screen);
    SDL_Quit();
    return EXIT_SUCCESS;
}
