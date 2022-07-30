#ifndef GAME_H
#define GAME_H

#include <stdbool.h>

#define WIDTH 1280
#define HEIGHT 480
#define SQUARE_SIZE 4

// Internal representation of Conway's Game of Life board
struct Game {
    bool board[HEIGHT][WIDTH];
};


#endif
