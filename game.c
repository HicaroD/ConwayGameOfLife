#include "game.h"
#include <SDL2/SDL.h>

SDL_Rect build_rect(int x, int y) {
    SDL_Rect rectangle = { x, y, SQUARE_SIZE, SQUARE_SIZE};
    return rectangle;
}

int draw_rect(SDL_Renderer* renderer, int x, int y) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_Rect rect = build_rect(x, y);
    return SDL_RenderFillRect(renderer, &rect);
}
