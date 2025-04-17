#include <iostream>
#include <string>
#include "pacmangame.h"

Direction getDirectionInput(const std::string& who) {
    std::string input;
    while (true) {
        std::cout << who << " move (U/D/L/R): ";
        std::cin >> input;
        if (input.length() != 1) {
            std::cout << "Please enter one letter.\n";
            continue;
        }
        char c = toupper(input[0]);
        if (c == 'U') return UP;
        if (c == 'D') return DOWN;
        if (c == 'L') return LEFT;
        if (c == 'R') return RIGHT;
        std::cout << "Invalid input. Use U, D, L, R.\n";
    }
}

bool askToPlayAgain() {
    char c;
    while (true) {
        std::cout << "Play again? (y/n): ";
        std::cin >> c;
        if (c == 'y' || c == 'Y') return true;
        if (c == 'n' || c == 'N') return false;
        std::cout << "Invalid input. Enter y or n.\n";
    }
}

void printRules() {
    std::cout << "PAC-MAN GRID CHASE RULES:\n";
    std::cout << "(PLAYER 1) Pac-Man (P) collects all pellets (.) to win.\n";
    std::cout << "(PLAYER 2) Ghost (G) tries to catch Pac-Man.\n";
    std::cout << "Players take turns using U(UP), D(DOWN), L(LEFT), R(RIGHT) to move.\n\n";
}

int main() {
    do {
        PacmanGame game;
        printRules();

        bool isPacmanTurn = true;

        while (game.status() == ONGOING) {
            std::cout << game;
            std::string player = isPacmanTurn ? "Pac-Man" : "Ghost";
            Direction dir = getDirectionInput(player);
            game.play(dir);
            game.nextTurn();
            isPacmanTurn = !isPacmanTurn;
        }

        std::cout << game;

        if (game.status() == PACMAN_WINS) {
            std::cout << "Pac-Man wins!\n";
        }
        else if (game.status() == GHOST_WINS) {
            std::cout << "Ghost wins!\n";
        }

    } while (askToPlayAgain());

    return 0;
}