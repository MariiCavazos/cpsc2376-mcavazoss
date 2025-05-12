#include "game.h"
#include <SDL2/SDL_ttf.h>
#include <iostream>

Game::Game(SDL_Renderer* renderer)
    : renderer(renderer), font(nullptr), gameOver(false), gameWon(false), score(0),
    pacmanRow(1), pacmanCol(1), pacmanDirection(RIGHT), lastMoveTime(0), moveDelay(200) { // Initialize timer
    // Initialize SDL_ttf for font rendering
    if (TTF_Init() == -1) {
        SDL_Log("TTF_Init failed: %s", TTF_GetError());
    }

    // Load the Arial font
    font = TTF_OpenFont("C:\\Windows\\Fonts\\arial.ttf", 24);
    if (!font) {
        SDL_Log("Failed to load font: %s", TTF_GetError());
    }

    // Load the maze layout
    loadMaze();

    // Initialize ghosts
    ghosts.push_back({ 10, 10, LEFT }); 
}

Game::~Game() {
    if (font) {
        TTF_CloseFont(font);
    }
    TTF_Quit();
}

void Game::loadMaze() {
    // maze layout (1 = wall, 2 = pellet, 3 = power-up, 0 = empty)
    int layout[MAZE_ROWS][MAZE_COLS] = {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1},
        {1, 2, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1},
        {1, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 2, 1},
        {1, 2, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 2, 1},
        {1, 2, 1, 0, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 0, 1, 1, 2, 1},
        {1, 2, 1, 0, 1, 2, 1, 1, 1, 0, 1, 1, 1, 2, 1, 0, 1, 1, 2, 1},
        {1, 2, 1, 0, 1, 2, 1, 0, 0, 0, 0, 0, 1, 2, 1, 0, 1, 1, 2, 1},
        {1, 2, 1, 0, 1, 2, 1, 0, 1, 1, 1, 0, 1, 2, 1, 0, 1, 1, 2, 1},
        {1, 2, 0, 0, 0, 0, 1, 0, 1, 2, 1, 0, 1, 2, 0, 0, 0, 0, 2, 1},
        {1, 2, 1, 0, 1, 2, 1, 0, 1, 2, 0, 0, 1, 2, 1, 0, 1, 1, 2, 1},
        {1, 2, 1, 0, 1, 2, 1, 0, 1, 1, 1, 0, 1, 2, 1, 0, 1, 1, 2, 1},
        {1, 2, 1, 0, 1, 2, 1, 0, 0, 0, 0, 0, 1, 2, 1, 0, 1, 1, 2, 1},
        {1, 2, 1, 0, 1, 2, 1, 1, 1, 0, 1, 1, 1, 2, 1, 0, 1, 1, 2, 1},
        {1, 2, 1, 0, 1, 3, 2, 2, 2, 2, 2, 2, 2, 2, 1, 0, 1, 1, 2, 1},
        {1, 2, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 2, 1},
        {1, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 2, 1},
        {1, 2, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1},
        {1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    };

    for (int i = 0; i < MAZE_ROWS; ++i) {
        for (int j = 0; j < MAZE_COLS; ++j) {
            maze[i][j] = static_cast<MazeElement>(layout[i][j]);
        }
    }
}

void Game::setPacmanDirection(Direction direction) {
    pacmanDirection = direction;
}

void Game::movePacman() {
    Uint32 currentTime = SDL_GetTicks(); // Get the current time
    if (currentTime - lastMoveTime < moveDelay) {
        return; // Skip movement if the delay hasn't passed
    }

    lastMoveTime = currentTime; // Update the last move time

    int newRow = pacmanRow;
    int newCol = pacmanCol;

    switch (pacmanDirection) {
    case UP:    newRow--; break;
    case DOWN:  newRow++; break;
    case LEFT:  newCol--; break;
    case RIGHT: newCol++; break;
    }

    if (!checkCollision(newRow, newCol)) {
        pacmanRow = newRow;
        pacmanCol = newCol;
        checkPellet();
    }
}

void Game::moveGhosts() {
    for (auto& ghost : ghosts) {
        int newRow = ghost.row;
        int newCol = ghost.col;

        switch (ghost.direction) {
        case UP:    newRow--; break;
        case DOWN:  newRow++; break;
        case LEFT:  newCol--; break;
        case RIGHT: newCol++; break;
        }

        if (!checkCollision(newRow, newCol)) {
            ghost.row = newRow;
            ghost.col = newCol;
        }
        else {
            ghost.direction = static_cast<Direction>(rand() % 4);
        }

        if (ghost.row == pacmanRow && ghost.col == pacmanCol) {
            gameOver = true;
        }
    }
}

bool Game::checkCollision(int row, int col) {
    return maze[row][col] == WALL;
}

void Game::checkPellet() {
    if (maze[pacmanRow][pacmanCol] == PELLET) {
        maze[pacmanRow][pacmanCol] = EMPTY;
        score += 10;
    }
    else if (maze[pacmanRow][pacmanCol] == POWER_UP) {
        maze[pacmanRow][pacmanCol] = EMPTY;
        score += 50;
    }
}

void Game::checkWinLoss() {
    for (int i = 0; i < MAZE_ROWS; ++i) {
        for (int j = 0; j < MAZE_COLS; ++j) {
            if (maze[i][j] == PELLET || maze[i][j] == POWER_UP) {
                return;
            }
        }
    }
    gameWon = true;
    gameOver = true;
}

void Game::update() {
    if (!gameOver) {
        movePacman();
        moveGhosts();
        checkWinLoss();
    }
}

void Game::draw(SDL_Renderer* renderer) {
    for (int i = 0; i < MAZE_ROWS; ++i) {
        for (int j = 0; j < MAZE_COLS; ++j) {
            SDL_Rect cell = { j * CELL_SIZE, i * CELL_SIZE, CELL_SIZE, CELL_SIZE };

            SDL_Rect pellet = { 0, 0, 0, 0 };
            SDL_Rect powerUp = { 0, 0, 0, 0 };

            switch (maze[i][j]) {
            case WALL:
                SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
                SDL_RenderFillRect(renderer, &cell);
                break;
            case PELLET:
                pellet = { cell.x + CELL_SIZE / 4, cell.y + CELL_SIZE / 4, CELL_SIZE / 2, CELL_SIZE / 2 };
                SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
                SDL_RenderFillRect(renderer, &pellet);
                break;
            case POWER_UP:
                powerUp = { cell.x + CELL_SIZE / 4, cell.y + CELL_SIZE / 4, CELL_SIZE / 2, CELL_SIZE / 2 };
                SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
                SDL_RenderFillRect(renderer, &powerUp);
                break;
            default:
                break;
            }
        }
    }

    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
    SDL_Rect pacman = { pacmanCol * CELL_SIZE + 5, pacmanRow * CELL_SIZE + 5, CELL_SIZE - 10, CELL_SIZE - 10 };
    SDL_RenderFillRect(renderer, &pacman);

    for (const auto& ghost : ghosts) {
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_Rect ghostRect = { ghost.col * CELL_SIZE + 5, ghost.row * CELL_SIZE + 5, CELL_SIZE - 10, CELL_SIZE - 10 };
        SDL_RenderFillRect(renderer, &ghostRect);
    }

    renderText("Score: " + std::to_string(score), 10, MAZE_ROWS * CELL_SIZE + 20);

    if (gameWon) {
        renderText("You Win! Press R to Restart", 10, MAZE_ROWS * CELL_SIZE + 50);
    }
    else if (gameOver) {
        renderText("Game Over! Press R to Restart", 10, MAZE_ROWS * CELL_SIZE + 50);
    }
}

void Game::renderText(const std::string& message, int x, int y) {
    SDL_Color color = { 255, 255, 255 };
    SDL_Surface* surface = TTF_RenderText_Solid(font, message.c_str(), color);
    if (!surface) {
        SDL_Log("Failed to create text surface: %s", TTF_GetError());
        return;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture) {
        SDL_Log("Failed to create text texture: %s", SDL_GetError());
        SDL_FreeSurface(surface);
        return;
    }

    int textWidth = surface->w;
    int textHeight = surface->h;
    SDL_FreeSurface(surface);

    SDL_Rect textRect = { x, y, textWidth, textHeight };
    SDL_RenderCopy(renderer, texture, NULL, &textRect);
    SDL_DestroyTexture(texture);
}

void Game::restartGame() {
    gameOver = false;
    gameWon = false;
    score = 0;
    pacmanRow = 1;
    pacmanCol = 1;
    pacmanDirection = RIGHT;
    lastMoveTime = 0; // Reset the timer
    loadMaze();
    ghosts.clear();
    ghosts.push_back({ 10, 10, LEFT });
}