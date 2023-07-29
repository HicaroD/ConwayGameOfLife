#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include <utility>
#include <vector>

#define SCALE_FACTOR 10
#define WIDTH 100
#define HEIGHT 70

struct Cell {
  bool alive;
  int x, y;
};

Cell new_cell(int x, int y);

struct Game {
  Cell grid[HEIGHT][WIDTH];
};

Game *new_game(std::vector<std::pair<int, int>> &seed);

void draw_game_board(Game *game, SDL_Renderer *renderer);

void update_game_board(Game *game);

void set_cell_state_color(SDL_Renderer *renderer, Cell cell);

int count_cell_neighbors(Game *game, Cell *cell);

#endif
