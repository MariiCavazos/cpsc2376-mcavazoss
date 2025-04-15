# Board Game Lending System Design

## 1. Program Specification

This system is designed to manage board games at a local board game café. The system will track the games in the inventory, who has borrowed them, and when they are due for return. It allows the café owner to:

- See a list of all the games available and how many copies are in stock.
- Track which customer has borrowed which game.
- Record when games are returned.

## 2. Key Nouns and Verbs

### Nouns:
- **Game**: Board games available for borrowing.
- **Customer**: People who borrow games.
- **Loan**: The act of borrowing a game.
- **GameLibrary**: The system that holds all game information.

### Verbs:
- **Checkout**: Borrow a game.
- **Return**: Return a game.
- **List**: Show available games.

## 3. Class Design

### Class: `Game`

```cpp
class Game {
public:
    string title;
    string publisher;
    int totalCopies;v
    int availableCopies;
    
    Game(string, string, int);
    void checkout();
    void returnCopy();
};

[Google](https://www.google.com)

```mermaid
flowchart LR
A --> B
B --> C