#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <utility>
#include <SDL2/SDL.h>

#include "game.hpp"

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

std::vector<std::pair<int, int>> read_seed_file() {
    std::vector<std::pair<int, int>> seed = {};

    std::ifstream file("seed.txt");
    std::string line;

    while(std::getline(file, line)) {
	std::istringstream iss(line);
	int x, y;
	if(!(iss >> x >> y)) break;
	seed.push_back(std::make_pair(x, y));
    }
    return seed;
}

int main() {
    SDL_Window* screen;
    SDL_Renderer* renderer;

    check_sdl_error(SDL_Init(SDL_INIT_VIDEO));

    screen = SDL_CreateWindow("Conway's Game of Life", 0, 0, WIDTH * SCALE_FACTOR, HEIGHT * SCALE_FACTOR, SDL_WINDOW_SHOWN);
    check_sdl_pointer_error(screen);

    renderer = SDL_CreateRenderer(screen, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    check_sdl_pointer_error(renderer);

    std::vector<std::pair<int, int>> seed = read_seed_file();
    Game* game = new_game(seed);
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

    delete game;
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(screen);
    SDL_Quit();
    return EXIT_SUCCESS;
}
