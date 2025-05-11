#pragma once
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <vector>

const int GRID_SIZE = 10;
const int CELL_SIZE = 64;

enum Entity { EMPTY, PACMAN, GHOST, PELLET };
enum Direction { UP, DOWN, LEFT, RIGHT };
enum Status { ONGOING, PACMAN_WINS, GHOST_WINS };

struct Position {
    int row;
    int col;
};

class Game {
public:
    Game();
    void play(Direction dir);
    void draw(SDL_Renderer* renderer);
    Status status() const;

private:
    std::vector<std::vector<Entity>> board;
    Position pacman;
    Position ghost;
    bool isPacmanTurn;
    Status gameStatus;

    Position move(Position current, Direction dir) const;
    bool isValid(Position pos) const;
    void updateBoard(Position& playerPos, Entity playerType, Direction dir);
};
