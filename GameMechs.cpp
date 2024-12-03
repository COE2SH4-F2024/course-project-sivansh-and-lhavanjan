#include "GameMechs.h"
#include "MacUILib.h"

// Default constructor for GameMechs class
GameMechs::GameMechs() {
    input = 0;            // Initialize input to 0
    exitFlag = false;     // Initialize exitFlag to false
    loseFlag = false;     // Initialize loseFlag to false
    score = 0;            // Initialize score to 0

    boardSizeX = 30;      // Set default board width
    boardSizeY = 15;      // Set default board height
}

// Additional constructor for GameMechs class
GameMechs::GameMechs(int boardX, int boardY) {
    input = 0;            // Initialize input to 0
    exitFlag = false;     // Initialize exitFlag to false
    loseFlag = false;     // Initialize loseFlag to false
    score = 0;            // Initialize score to 0

    boardSizeX = boardX;  // Set board width to given value
    boardSizeY = boardY;  // Set board height to given value
}

// Copy constructor for GameMechs class
GameMechs::GameMechs(const GameMechs &game) {
    input = 0;            // Initialize input to 0
    exitFlag = false;     // Initialize exitFlag to false
    loseFlag = false;     // Initialize loseFlag to false
    score = 0;            // Initialize score to 0

    boardSizeX = 30;      // Set default board width
    boardSizeY = 15;      // Set default board height
}

// Assignment operator for GameMechs class
GameMechs &GameMechs::operator=(const GameMechs &game) {
    if (this != &game) {  // Check for self-assignment
        this->boardSizeX = 30;  // Set default board width
        this->boardSizeY = 15;  // Set default board height
        this->input = 0;        // Initialize input to 0
        this->exitFlag = false; // Initialize exitFlag to false
        this->loseFlag = false; // Initialize loseFlag to false
        this->score = 0;        // Initialize score to 0
    }
    return *this;         // Return the current object
}

// Destructor for GameMechs class
GameMechs::~GameMechs() {
}

// Get the status of the exit flag
bool GameMechs::getExitFlagStatus() const {
    return exitFlag;
}

// Get the status of the lose flag
bool GameMechs::getLoseFlagStatus() const {
    return loseFlag;
}

// Get the current input character
char GameMechs::getInput() {
    if (MacUILib_hasChar()) {  // Check if there is a character input
        input = MacUILib_getChar();  // Get the character input
    }
    return input;  // Return the current input
}

// Get the current score
int GameMechs::getScore() const {
    return score;
}

// Increment the score by a specified amount
void GameMechs::incrementScore(int amount) {
    score += amount;
}

// Get the board width
int GameMechs::getBoardSizeX() const {
    return boardSizeX;
}

// Get the board height
int GameMechs::getBoardSizeY() const {
    return boardSizeY;
}

// Set the exit flag to true
void GameMechs::setExitTrue() {
    exitFlag = true;
}

// Set the lose flag to true
void GameMechs::setLoseFlag() {
    loseFlag = true;
}

// Set the input character
void GameMechs::setInput(char this_input) {
    input = this_input;
}

// Clear the input character
void GameMechs::clearInput() {
    input = 0;
}

// Get the current speed
int GameMechs::getSpeed() {
    return speed;
}

// Set the speed to a new value within a valid range
void GameMechs::setSpeed(int newSpeed) {
    if (newSpeed >= 1 && newSpeed <= 5) {
        speed = newSpeed;
    }
}

// Get the current delay amount
int GameMechs::getDelayAmount() {
    return delayAmount;
}

// Set the delay amount to a new value
void GameMechs::setDelayAmount(int amount) {
    delayAmount = amount;
}
