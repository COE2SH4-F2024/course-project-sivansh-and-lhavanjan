#ifndef GAMEMECHS_H
#define GAMEMECHS_H

#include <cstdlib>
#include <time.h>

#include "objPos.h"
#include "objPosArrayList.h"

using namespace std;

// Class representing the game mechanics
class GameMechs {
private:
    char input;                // Character input from the user
    bool exitFlag;             // Flag to indicate if the game should exit
    bool loseFlag;             // Flag to indicate if the player has lost
    int score;                 // Current score of the player

    int boardSizeX;            // Width of the game board
    int boardSizeY;            // Height of the game board

    objPos food;               // Position of the food on the board

    int speed = 3;             // Speed of the game
    int delayAmount = 100000;  // Delay amount for game speed control

public:
    GameMechs();                               // Default constructor
    GameMechs(int boardX, int boardY);         // Parameterized constructor
    ~GameMechs();                              // Destructor
    GameMechs(const GameMechs &game);          // Copy constructor
    GameMechs &operator=(const GameMechs &game); // Assignment operator

    bool getExitFlagStatus() const;            // Get the status of the exit flag
    void setExitTrue();                        // Set the exit flag to true
    bool getLoseFlagStatus() const;            // Get the status of the lose flag
    void setLoseFlag();                        // Set the lose flag to true

    char getInput();                           // Get the current input character
    void setInput(char this_input);            // Set the input character
    void clearInput();                         // Clear the input character

    int getBoardSizeX() const;                 // Get the board width
    int getBoardSizeY() const;                 // Get the board height

    int getScore() const;                      // Get the current score
    void incrementScore(int amount);           // Increment the score by a specified amount
    int getSpeed();                            // Get the current speed
    void setSpeed(int newSpeed);               // Set the speed to a new value
    int getDelayAmount();                      // Get the current delay amount
    void setDelayAmount(int amount);           // Set the delay amount to a new value
};

#endif