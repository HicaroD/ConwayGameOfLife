#ifndef GAME_H
#define GAME_H

#include <stdbool.h>
#include <SDL2/SDL.h>

#define WIDTH 1280
#define HEIGHT 480
#define SQUARE_SIZE 10

enum CellState {
    Dead = 0,
    Alive = 1
};

struct Cell {
    enum CellState state;
    int x, y;
};

struct Cell* new_cell(int x, int y);

struct Game {
    struct Cell* grid[HEIGHT][WIDTH];
};

struct Game* new_game();

void draw_game_board(struct Game* game, SDL_Renderer* renderer);

void update_game_board(struct Game* game);

void set_cell_state_color(SDL_Renderer* renderer, struct Cell* cell);

// Helpers
bool is_alive(struct Cell* cell);

int count_cell_neighbors(struct Game* game, struct Cell* cell);

SDL_Rect build_rect(int x, int y);

#endif
