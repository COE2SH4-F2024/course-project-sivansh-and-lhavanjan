#ifndef PLAYER_H
#define PLAYER_H

#include "GameMechs.h"
#include "objPos.h"
#include "objPosArrayList.h"

class Player
{
    // Construct the remaining declaration from the project manual.

    // Only some sample members are included here

    // You will include more data members and member functions to complete your design.

    
    public:
        enum Dir {UP, DOWN, LEFT, RIGHT, STOP};  // This is the direction state

        // Player(GameMechs* thisGMRef);
        Player(GameMechs* thisGMRef, int initalLength);
        ~Player();

        // objPos getPlayerPos() const; // Upgrade this in iteration 3.       
        objPosArrayList* getPlayerPos() const;
        void updatePlayerDir();
        void movePlayer();

        // More methods to be added here
        void speedControl();

    private:
        objPosArrayList* playerPosList; // Upgrade this in iteration 3.
        // objPos playerPos;       
        enum Dir playerdirection;

        // Need a reference to the Main Game Mechanisms
        GameMechs* mainGameMechsRef;
};

#endif