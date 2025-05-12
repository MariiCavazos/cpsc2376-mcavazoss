#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include "game.h"

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("Pac-Man Game",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        MAZE_COLS * CELL_SIZE, MAZE_ROWS * CELL_SIZE + 100, SDL_WINDOW_SHOWN); 
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    Game game(renderer);

    bool running = true;
    SDL_Event event;
    Uint32 lastUpdateTime = SDL_GetTicks();

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
            else if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                case SDLK_UP:
                    game.setPacmanDirection(UP);
                    break;
                case SDLK_DOWN:
                    game.setPacmanDirection(DOWN);
                    break;
                case SDLK_LEFT:
                    game.setPacmanDirection(LEFT);
                    break;
                case SDLK_RIGHT:
                    game.setPacmanDirection(RIGHT);
                    break;
                case SDLK_r:
                    game.restartGame();
                    break;
                case SDLK_ESCAPE:
                    running = false;
                    break;
                }
            }
        }

        Uint32 currentTime = SDL_GetTicks();
        if (currentTime - lastUpdateTime > 100) {
            game.update();
            lastUpdateTime = currentTime;
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        game.draw(renderer);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}