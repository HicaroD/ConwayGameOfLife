#ifndef GAME_H
#define GAME_H

#include <stdbool.h>
#include <SDL2/SDL.h>

#define SCALE_FACTOR 20
#define WIDTH 64
#define HEIGHT 32
#define SCREEN_WIDTH 1280 
#define SCREEN_HEIGHT 640 

enum CellState {
    Dead = 0,
    Alive = 1
};

struct Cell {
    enum CellState state;
    int x, y;
};

struct Cell new_cell(int x, int y);

struct Game {
    struct Cell grid[HEIGHT][WIDTH];
};

struct Game* new_game(size_t seed_rows, int seed[seed_rows][2]);

void draw_game_board(struct Game* game, SDL_Renderer* renderer);

void update_game_board(struct Game* game);

void set_cell_state_color(SDL_Renderer* renderer, struct Cell cell);

int count_cell_neighbors(struct Game* game, struct Cell* cell);

bool is_cell_on_edge(struct Cell* cell);

#endif
