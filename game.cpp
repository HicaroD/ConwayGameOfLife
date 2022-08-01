#include <SDL2/SDL.h>
#include <vector>
#include <utility>
#include <iostream>

#include "game.hpp"

Cell new_cell(int x, int y) {
    struct Cell cell = { Dead, x, y };
    return cell;
}

Game* new_game(std::vector<std::pair<int, int>>& seed) {
    Game* game = new Game;

    for(int i = 0; i < HEIGHT; i++) {
        for(int j = 0; j < WIDTH; j++) {
            game->grid[i][j] = new_cell(j, i);
        }
    }

    for(auto &coordinate : seed) {
        int x = coordinate.first;
        int y = coordinate.second;
        game->grid[y][x].state = Alive;
    }

    return game;
}

bool is_cell_on_edge(Cell* cell) {
    int x = cell->x;
    int y = cell->y;
    return x == 0 || y == 0 || y + 1 >= HEIGHT || x + 1 >= WIDTH;
}

void update_game_board(Game* game) {
    for(int h = 0; h < HEIGHT; h++) {
        for(int w = 0; w < WIDTH; w++) {
            struct Cell current_cell = game->grid[h][w];

            int neighbours = count_cell_neighbors(game, &current_cell);
            if(current_cell.state == Alive && (neighbours < 2 || neighbours > 3)) {
                game->grid[h][w].state = Dead;
            } else if(current_cell.state == Dead && neighbours == 3) {
                game->grid[h][w].state = Alive;
            }
        }
    }
}

int count_cell_neighbors(Game* game, Cell* cell) {
    int sum = 0;
    int x_axis = cell->x;
    int y_axis = cell->y;

    for(int y = -1; y < 2; y++) {
        for(int x = -1; x < 2; x++) {
            int rows = (y_axis + y + HEIGHT) % HEIGHT;
            int columns = (x_axis + x + WIDTH) % WIDTH;
            sum += (game->grid[rows][columns]).state;
        }
    }

    // The cell itself will not be counted as a neighbour
    sum -= game->grid[y_axis][x_axis].state;
    return sum;
}

void set_cell_state_color(SDL_Renderer* renderer, Cell cell) {
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

void draw_game_board(Game* game, SDL_Renderer* renderer) {
    for(int h = 0; h < HEIGHT; h++) {
        for(int w = 0; w < WIDTH; w++) {
            set_cell_state_color(renderer, game->grid[h][w]);
            SDL_Rect rect = { w * SCALE_FACTOR, h * SCALE_FACTOR, SCALE_FACTOR, SCALE_FACTOR};
            SDL_RenderDrawRect(renderer, &rect);
        }
    }
}
