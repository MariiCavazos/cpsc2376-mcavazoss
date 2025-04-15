#include <iostream>
#include <vector>
#include <limits>
#include <cstdlib>

enum class Entity { EMPTY, PACMAN, GHOST, PELLET };
enum class GameState { ONGOING, PACMAN_WINS, GHOST_WINS };
enum class Direction { UP, DOWN, LEFT, RIGHT };

const int GRID_SIZE = 10;

struct Position {
    int row;
    int col;
};

void makeBoard(std::vector<std::vector<Entity>>& board, Position& pacman, Position& ghost) {
    board = std::vector<std::vector<Entity>>(GRID_SIZE, std::vector<Entity>(GRID_SIZE, Entity::PELLET));

    pacman = { 0, 0 };
    ghost = { GRID_SIZE - 1, GRID_SIZE - 1 };

    board[pacman.row][pacman.col] = Entity::PACMAN;
    board[ghost.row][ghost.col] = Entity::GHOST;
}

void printBoard(const std::vector<std::vector<Entity>>& board) {
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            switch (board[i][j]) {
            case Entity::EMPTY: std::cout << "  "; break;
            case Entity::PELLET: std::cout << ". "; break;
            case Entity::PACMAN: std::cout << "P "; break;
            case Entity::GHOST: std::cout << "G "; break;
            }
        }
        std::cout << std::endl;
    }
}

Direction getDirectionInput(const std::string& who) {
    std::string input;
    while (true) {
        std::cout << who << " move (U/D/L/R): ";
        std::cin >> input;
        if (input.length() != 1) {
            std::cout << "Please enter only one character." << std::endl;
            continue;
        }
        char dir = toupper(input[0]);
        if (dir == 'U') return Direction::UP;
        if (dir == 'D') return Direction::DOWN;
        if (dir == 'L') return Direction::LEFT;
        if (dir == 'R') return Direction::RIGHT;
        std::cout << "Invalid input. Use U/D/L/R keys." << std::endl;
    }
}

bool isValid(Position pos) {
    return pos.row >= 0 && pos.row < GRID_SIZE && pos.col >= 0 && pos.col < GRID_SIZE;
}

Position move(Position current, Direction dir) {
    Position newPos = current;
    switch (dir) {
    case Direction::UP: newPos.row -= 1; break;
    case Direction::DOWN: newPos.row += 1; break;
    case Direction::LEFT: newPos.col -= 1; break;
    case Direction::RIGHT: newPos.col += 1; break;
    }
    return newPos;
}

GameState gameStatus(const std::vector<std::vector<Entity>>& board, Position pacman, Position ghost) {
    if (pacman.row == ghost.row && pacman.col == ghost.col) {
        return GameState::GHOST_WINS;
    }
    for (const auto& row : board) {
        for (const auto& cell : row) {
            if (cell == Entity::PELLET) return GameState::ONGOING;
        }
    }
    return GameState::PACMAN_WINS;
}

void play(std::vector<std::vector<Entity>>& board, Position& playerPos, Entity playerType, Direction dir) {
    Position newPos = move(playerPos, dir);
    if (!isValid(newPos)) return;

    if (playerType == Entity::PACMAN && board[newPos.row][newPos.col] == Entity::GHOST) {
        playerPos = newPos;
        return;
    }

    board[playerPos.row][playerPos.col] = Entity::EMPTY;

    if (playerType == Entity::PACMAN) {
        board[newPos.row][newPos.col] = Entity::PACMAN;
    }
    else {
        if (board[newPos.row][newPos.col] == Entity::PELLET) {
            board[newPos.row][newPos.col] = Entity::EMPTY;
        }
        board[newPos.row][newPos.col] = Entity::GHOST;
    }

    playerPos = newPos;
}

bool askToPlayAgain() {
    char c;
    while (true) {
        std::cout << "Play again? (y/n): ";
        std::cin >> c;
        if (c == 'y' || c == 'Y') return true;
        if (c == 'n' || c == 'N') return false;
        std::cout << "Invalid input. Enter y or n." << std::endl;
    }
}

void printRules() {
    std::cout << "PAC-MAN GRID CHASE RULES:" << std::endl;
    std::cout << "Pac-Man (P) tries to collect all pellets (.)" << std::endl;
    std::cout << "Ghost (G) tries to catch Pac-Man." << std::endl;
    std::cout << "Players take turns moving using U(UP)/D(DOWN)/L(LEFT)/R(RIGHT)." << std::endl;
    std::cout << "If Ghost reaches Pac-Man, Ghost wins." << std::endl;
    std::cout << "If Pac-Man eats all pellets, Pac-Man wins." << std::endl << std::endl;
}

int main() {
    do {
        std::vector<std::vector<Entity>> board;
        Position pacman, ghost;

        makeBoard(board, pacman, ghost);
        printRules();
        GameState state = GameState::ONGOING;

        while (state == GameState::ONGOING) {
            printBoard(board);
            Direction pacDir = getDirectionInput("Pac-Man");
            play(board, pacman, Entity::PACMAN, pacDir);
            state = gameStatus(board, pacman, ghost);
            if (state != GameState::ONGOING) break;

            printBoard(board);
            Direction ghostDir = getDirectionInput("Ghost");
            play(board, ghost, Entity::GHOST, ghostDir);
            state = gameStatus(board, pacman, ghost);
        }

        printBoard(board);
        if (state == GameState::PACMAN_WINS) {
            std::cout << "Pac-Man wins!" << std::endl;
        }
        else if (state == GameState::GHOST_WINS) {
            std::cout << "Ghost wins!" << std::endl;
        }

    } while (askToPlayAgain());

    return 0;
}