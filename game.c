#include <SDL2/SDL.h>
#include <stdlib.h>
#include "game.h"

// FIXME: Is a malloc really necessary here? (performance issues because I'm doing over six millions malloc calls)
struct Cell* new_cell(int x, int y) {
    struct Cell* cell = (struct Cell*)malloc(sizeof(struct Cell));
    cell->state = Dead;
    cell->x = x;
    cell->y = y;
    return cell;
}

// TODO: Get initial state of the game (store coordinates on a text file)
struct Game* new_game() {
    struct Game* game = (struct Game*)malloc(sizeof(struct Game));

    for(int i = 0; i < HEIGHT; i++) {
	for(int j = 0; j < WIDTH; j++) {
	    game->grid[i][j] = new_cell(j, i);
	}
    }

    return game;
}

SDL_Rect build_rect(int x, int y) {
    SDL_Rect rectangle = { x, y, SQUARE_SIZE, SQUARE_SIZE};
    return rectangle;
}

bool is_alive(struct Cell* cell) {
    return cell->state == Alive;
}

void update_game_board(struct Game* game) {
    for(int h = 0; h < HEIGHT; h++) {
	for(int w = 0; w < WIDTH; w++) {
	    // Check neibourghs of each cell and apply rules
	    printf("%d\n", game->grid[h][w]->state);
	}
    }
}

int count_cell_neighbors(struct Game* game, struct Cell* cell) {
    int sum = 0;
    int x = cell->x;
    int y = cell->y;

    // TODO: Refactor this code (too verbose)
    sum += (game->grid[y - 1 < 0 ? y : y - 1][x - 1 < 0 ? x : x - 1])->state;
    sum += (game->grid[y - 1 < 0 ? y : y - 1][x])->state;
    sum += (game->grid[y - 1 < 0 ? y : y - 1][x + 1 > WIDTH ? x : x - 1])->state;

    sum += (game->grid[y][x - 1 < 0 ? x : x - 1])->state;
    sum += (game->grid[y][x])->state;
    sum += (game->grid[y][x + 1 > WIDTH ? x : x - 1])->state;

    sum += (game->grid[y + 1 > HEIGHT ? y : y + 1][x - 1 < 0 ? x : x - 1])->state;
    sum += (game->grid[y + 1 > HEIGHT ? y : y + 1][x])->state;
    sum += (game->grid[y + 1 > HEIGHT ? y : y + 1][x + 1 > WIDTH ? x : x - 1])->state;

    return sum;
}

void set_cell_state_color(SDL_Renderer* renderer, struct Cell* cell) {
	switch(cell->state) {
	    case Alive:
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		break;
	    case Dead:
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
		break;

	    default:
		printf("Invalid state. This should never happen!");
		break;
	}
}

void draw_game_board(struct Game* game, SDL_Renderer* renderer) {
    for(int h = 0; h < HEIGHT; h++) {
	for(int w = 0; w < WIDTH; w++) {
	    set_cell_state_color(renderer, game->grid[h][w]);
	    SDL_Rect rect = build_rect(w, h);
	    SDL_RenderFillRect(renderer, &rect);
	}
    }
}
