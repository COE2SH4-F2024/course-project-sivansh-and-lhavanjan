#ifndef PLAYER_H
#define PLAYER_H

#include "GameMechs.h"          // Include the GameMechs class definition
#include "objPos.h"             // Include the objPos class definition
#include "objPosArrayList.h"    // Include the objPosArrayList class definition
#include "Food.h"               // Include the Food class definition

// Class representing a player in the game
class Player {
public:
    // Enumeration for player direction
    enum Dir {
        UP,    // Move up
        DOWN,  // Move down
        LEFT,  // Move left
        RIGHT, // Move right
        STOP   // Stop moving
    };

    // Constructor to initialize a Player object
    Player(GameMechs *thisGMRef, Food *thisFoodRef, int initialLength);
    // Destructor to clean up resources
    ~Player();

    // Copy constructor
    Player(const Player &a);
    // Assignment operator
    Player &operator=(const Player &a);

    // Get the current player position list
    objPosArrayList *getPlayerPos() const;
    // Update the player direction based on input
    void updatePlayerDir();
    // Move the player in the current direction
    void movePlayer();

    // Control the speed of the player
    void speedControl();

    // Check if the player has consumed food
    bool checkFoodConsumption(Food *foodRef);
    // Apply special effect based on food symbol
    void applySpecialFoodEffect(char foodSymbol);
    // Increase the length of the player
    void increasePlayerLength(int newX, int newY);
    // Check if the player has collided with itself
    bool checkSelfCollision();

private:
    objPosArrayList *playerPosList; // List of player positions
    Dir playerdirection;            // Current direction of the player

    GameMechs *mainGameMechsRef;    // Reference to game mechanics
    Food *foodRef;                  // Reference to food
};

#endif