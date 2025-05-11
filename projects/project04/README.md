# Project 04 – Pac-Man Grid Chase

## 🕹️ Description

Pac-Man Grid Chase is a turn-based 2-player grid game written in C++ using SDL2. One player controls Pac-Man who must collect all the pellets on the board, while the other controls the Ghost who tries to catch Pac-Man. The game alternates turns and ends when either all pellets are collected or Pac-Man is caught.

## 🎮 Controls

- Arrow Keys: Move the current player (Pac-Man or Ghost)
- `R`: Restart the game
- `Esc`: Quit the game

## 🧪 Screenshot

![Screenshot](screenshot.png)

## ✨ Extra Features

- Turn-based logic between Pac-Man and Ghost
- Grid-based rendering using SDL2
- Simple game reset with `R` key

---

## 🛠️ Build & Run Instructions

### Dependencies

Make sure SDL2 is installed on your system.

For Linux/macOS:
```bash
g++ -o pacmangame main.cpp game.cpp -lSDL2
./pacmangame