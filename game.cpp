#include <SDL2/SDL.h>
#include <iostream>
#include <utility>
#include <vector>

#include "game.hpp"

Cell new_cell(int x, int y) {
  struct Cell cell = {false, x, y};
  return cell;
}

Game *new_game(std::vector<std::pair<int, int>> &seed) {
  Game *game = new Game;

  for (int i = 0; i < HEIGHT; i++) {
    for (int j = 0; j < WIDTH; j++) {
      game->grid[i][j] = new_cell(j, i);
    }
  }

  for (auto &coordinate : seed) {
    int x = coordinate.first;
    int y = coordinate.second;
    game->grid[y][x].alive = true;
  }

  return game;
}

void update_game_board(Game *game) {
  Cell next_generation_grid[HEIGHT][WIDTH];
  for (int i = 0; i < HEIGHT; i++) {
    for (int j = 0; j < WIDTH; j++) {
      next_generation_grid[i][j] = new_cell(j, i);
    }
  }

  for (int h = 0; h < HEIGHT; h++) {
    for (int w = 0; w < WIDTH; w++) {
      struct Cell current_cell = game->grid[h][w];
      int neighbours = count_cell_neighbors(game, &current_cell);

      if (current_cell.alive && (neighbours < 2 || neighbours > 3)) {
        next_generation_grid[h][w].alive = false;
      } else if (!current_cell.alive && neighbours == 3) {
        next_generation_grid[h][w].alive = true;
      } else {
        next_generation_grid[h][w].alive = current_cell.alive;
      }
    }
  }

  for (int h = 0; h < HEIGHT; h++) {
    for (int w = 0; w < WIDTH; w++) {
      game->grid[h][w] = next_generation_grid[h][w];
    }
  }
}

int count_cell_neighbors(Game *game, Cell *cell) {
  int sum = 0;
  int x_axis = cell->x;
  int y_axis = cell->y;

  for (int y = -1; y < 2; y++) {
    for (int x = -1; x < 2; x++) {
      int rows = (y_axis + y + HEIGHT) % HEIGHT;
      int columns = (x_axis + x + WIDTH) % WIDTH;

      if (game->grid[rows][columns].alive)
        sum += 1;
    }
  }

  // The cell itself will not be counted as a neighbour
  if (game->grid[y_axis][x_axis].alive)
    sum -= 1;
  return sum;
}

void set_cell_state_color(SDL_Renderer *renderer, Cell cell) {
  if (cell.alive) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  } else {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
  }
}

void draw_game_board(Game *game, SDL_Renderer *renderer) {
  for (int h = 0; h < HEIGHT; h++) {
    for (int w = 0; w < WIDTH; w++) {
      set_cell_state_color(renderer, game->grid[h][w]);
      SDL_Rect rect = {w * SCALE_FACTOR, h * SCALE_FACTOR, SCALE_FACTOR,
                       SCALE_FACTOR};
      SDL_RenderDrawRect(renderer, &rect);
    }
  }
}
