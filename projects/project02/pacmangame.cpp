#include "pacmangame.h"

PacmanGame::PacmanGame() {
    board = std::vector<std::vector<Entity>>(GRID_SIZE, std::vector<Entity>(GRID_SIZE, PELLET));
    pacman = { 0, 0 };
    ghost = { GRID_SIZE - 1, GRID_SIZE - 1 };
    board[pacman.row][pacman.col] = PACMAN;
    board[ghost.row][ghost.col] = GHOST;
    isPacmanTurn = true;
    gameStatus = ONGOING;
}

Status PacmanGame::status() const {
    return gameStatus;
}

void PacmanGame::play(Direction dir) {
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
}

void PacmanGame::nextTurn() {
    isPacmanTurn = !isPacmanTurn;
}

Position PacmanGame::move(Position current, Direction dir) const {
    Position newPos = current;
    switch (dir) {
    case UP: newPos.row -= 1; break;
    case DOWN: newPos.row += 1; break;
    case LEFT: newPos.col -= 1; break;
    case RIGHT: newPos.col += 1; break;
    }
    return newPos;
}

bool PacmanGame::isValid(Position pos) const {
    return pos.row >= 0 && pos.row < GRID_SIZE && pos.col >= 0 && pos.col < GRID_SIZE;
}

void PacmanGame::updateBoard(Position& playerPos, Entity playerType, Direction dir) {
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

std::ostream& operator<<(std::ostream& os, const PacmanGame& game) {
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            switch (game.board[i][j]) {
            case EMPTY: os << "  "; break;
            case PELLET: os << ". "; break;
            case PACMAN: os << "P "; break;
            case GHOST: os << "G "; break;
            }
        }
        os << '\n';
    }
    return os;
}