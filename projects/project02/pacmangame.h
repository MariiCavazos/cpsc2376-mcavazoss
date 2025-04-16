#pragma once
#ifndef PACMANGAME_H
#define PACMANGAME_H

#include <vector>
#include <iostream>

const int GRID_SIZE = 10;

enum Entity { EMPTY, PACMAN, GHOST, PELLET };
enum Direction { UP, DOWN, LEFT, RIGHT };
enum Status { ONGOING, PACMAN_WINS, GHOST_WINS };

struct Position {
    int row;
    int col;
};

class PacmanGame {
public:
    PacmanGame();
    Status status() const;
    void play(Direction dir); 
    void nextTurn();
    friend std::ostream& operator<<(std::ostream& os, const PacmanGame& game);

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

#endif