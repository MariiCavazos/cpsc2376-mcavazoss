#include "game.h"

Game::Game() {
    board = std::vector<std::vector<Entity>>(GRID_SIZE, std::vector<Entity>(GRID_SIZE, PELLET));
    pacman = { 0, 0 };
    ghost = { GRID_SIZE - 1, GRID_SIZE - 1 };
    board[pacman.row][pacman.col] = PACMAN;
    board[ghost.row][ghost.col] = GHOST;
    isPacmanTurn = true;
    gameStatus = ONGOING;
}

Status Game::status() const {
    return gameStatus;
}

void Game::play(Direction dir) {
    if (gameStatus != ONGOING) return;

    if (isPacmanTurn) {
        updateBoard(pacman, PACMAN, dir);
    }
    else {
        updateBoard(ghost, GHOST, dir);
    }

    if (pacman.row == ghost.row && pacman.col == ghost.col) {
        gameStatus = GHOST_WINS;
        return;
    }

    bool pelletsLeft = false;
    for (const auto& row : board) {
        for (auto cell : row) {
            if (cell == PELLET) {
                pelletsLeft = true;
                break;
            }
        }
        if (pelletsLeft) break;
    }

    if (!pelletsLeft) gameStatus = PACMAN_WINS;

    isPacmanTurn = !isPacmanTurn;
}

void Game::draw(SDL_Renderer* renderer) {
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            SDL_Rect cell = { j * CELL_SIZE, i * CELL_SIZE, CELL_SIZE, CELL_SIZE };

            switch (board[i][j]) {
            case EMPTY:
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                break;
            case PELLET:
                SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
                break;
            case PACMAN:
                SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
                break;
            case GHOST:
                SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
                break;
            }
            SDL_RenderFillRect(renderer, &cell);
        }
    }
}

Position Game::move(Position current, Direction dir) const {
    Position newPos = current;
    switch (dir) {
    case UP: newPos.row -= 1; break;
    case DOWN: newPos.row += 1; break;
    case LEFT: newPos.col -= 1; break;
    case RIGHT: newPos.col += 1; break;
    }
    return newPos;
}

bool Game::isValid(Position pos) const {
    return pos.row >= 0 && pos.row < GRID_SIZE && pos.col >= 0 && pos.col < GRID_SIZE;
}

void Game::updateBoard(Position& playerPos, Entity playerType, Direction dir) {
    Position newPos = move(playerPos, dir);
    if (!isValid(newPos)) return;

    if (playerType == PACMAN && board[newPos.row][newPos.col] == GHOST) {
        playerPos = newPos;
        return;
    }

    board[playerPos.row][playerPos.col] = EMPTY;

    if (playerType == PACMAN) {
        board[newPos.row][newPos.col] = PACMAN;
    }
    else {
        if (board[newPos.row][newPos.col] == PELLET)
            board[newPos.row][newPos.col] = EMPTY;
        board[newPos.row][newPos.col] = GHOST;
    }

    playerPos = newPos;
}
