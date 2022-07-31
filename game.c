#include <SDL2/SDL.h>
#include <stdlib.h>
#include "game.h"

struct Cell new_cell(int x, int y) {
    struct Cell cell = { Dead, x, y };
    return cell;
}

struct Game* new_game(size_t rows, int seed[rows][2]) {
    struct Game* game = (struct Game*)malloc(sizeof(struct Game));

    for(int i = 0; i < HEIGHT; i++) {
	for(int j = 0; j < WIDTH; j++) {
	    game->grid[i][j] = new_cell(j, i);
	}
    }

    for(size_t row = 0; row < rows; row++) {
	int x = seed[row][0];
	int y = seed[row][1];
	game->grid[y][x].state = Alive;
    }

    return game;
}

bool is_cell_on_edge(struct Cell* cell) {
    int x = cell->x;
    int y = cell->y;
    return x == 0 || y == 0 || y + 1 >= HEIGHT || x + 1 >= WIDTH;
}

void update_game_board(struct Game* game) {
    for(int h = 0; h < HEIGHT; h++) {
	for(int w = 0; w < WIDTH; w++) {
	    struct Cell current_cell = game->grid[h][w];

	    if(!is_cell_on_edge(&current_cell)) {
		int neighbours = count_cell_neighbors(game, &current_cell);

		if(current_cell.state == Alive && (neighbours < 2 || neighbours > 3)) {
		    printf("Kill cell\n");
		    game->grid[h][w].state = Dead;
		} else if(current_cell.state == Dead && neighbours == 3) {
		    printf("Create cell\n");
		    game->grid[h][w].state = Alive;
		}
	    }
	}
    }
}

int count_cell_neighbors(struct Game* game, struct Cell* cell) {
    int sum = 0;
    int x_axis = cell->x;
    int y_axis = cell->y;

    for(int y = -1; y < 2; y++) {
	for(int x = -1; x < 2; x++) {
	    sum += (game->grid[y_axis + y][x_axis + x]).state;
	}
    }

    // The cell itself will not be counted as a neighbour
    sum -= game->grid[y_axis][x_axis].state;
    return sum;
}

void set_cell_state_color(SDL_Renderer* renderer, struct Cell cell) {
	switch(cell.state) {
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
	    SDL_Rect rect = { w * SCALE_FACTOR, h * SCALE_FACTOR, SCALE_FACTOR, SCALE_FACTOR};
	    SDL_RenderFillRect(renderer, &rect);
	}
    }
}
