#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <vector>
#include <utility>

#define SCALE_FACTOR 10
#define WIDTH 80
#define HEIGHT 70

enum CellState {
    Dead = 0,
    Alive = 1
};

struct Cell {
    CellState state;
    int x, y;
};

Cell new_cell(int x, int y);

struct Game {
    Cell grid[HEIGHT][WIDTH];
};

Game* new_game(std::vector<std::pair<int, int>>& seed);

void draw_game_board(Game* game, SDL_Renderer* renderer);

void update_game_board(Game* game);

void set_cell_state_color(SDL_Renderer* renderer, Cell cell);

int count_cell_neighbors(Game* game, Cell* cell);

bool is_cell_on_edge(Cell* cell);

#endif
