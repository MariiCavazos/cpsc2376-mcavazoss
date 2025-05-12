#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <vector>

// Constants for the maze
const int MAZE_ROWS = 20;
const int MAZE_COLS = 20;
const int CELL_SIZE = 30; // Each cell is 30x30 pixels

// Enum for maze elements
enum MazeElement { EMPTY, WALL, PELLET, POWER_UP };

// Directions for movement
enum Direction { UP, DOWN, LEFT, RIGHT };

class Game {
public:
    Game(SDL_Renderer* renderer);
    ~Game();

    void run(); // Main game loop
    void restartGame(); // Restart the game
    void draw(SDL_Renderer* renderer); // Render the game state
    void setPacmanDirection(Direction direction); // Set Pac-Man's direction
    void update(); // Update the game state

private:
    SDL_Renderer* renderer;
    TTF_Font* font;

    // Game state
    bool gameOver;
    bool gameWon;
    int score;

    // Maze and player
    MazeElement maze[MAZE_ROWS][MAZE_COLS]; // 2D array for the maze
    int pacmanRow, pacmanCol; // Pac-Man's position
    Direction pacmanDirection; // Pac-Man's current direction

    // Ghosts
    struct Ghost {
        int row, col;
        Direction direction;
    };
    std::vector<Ghost> ghosts;

    // Movement control
    Uint32 lastMoveTime; // Time of the last movement
    Uint32 moveDelay;    // Delay between movements in milliseconds

    // Helper methods
    void loadMaze(); // Load the maze layout
    void movePacman(); // Move Pac-Man
    void moveGhosts(); // Move ghosts
    bool checkCollision(int row, int col); // Check collision with walls
    void checkPellet(); // Check if Pac-Man eats a pellet or power-up
    void checkWinLoss(); // Check win/loss conditions
    void renderText(const std::string& message, int x, int y);
};

#endif