#include "Player.h"
#include "MacUILib.h"

int hasInput = 0;

Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    playerdirection = STOP;

    // more actions to be included
    playerPos.pos->x = mainGameMechsRef->getBoardSizeX() / 2;
    playerPos.pos->y = mainGameMechsRef->getBoardSizeY() / 2;
    playerPos.symbol = '@';
}


Player::~Player()
{
    // delete any heap members here
}

objPos Player::getPlayerPos() const
{
    // return the reference to the playerPos arrray list
    return playerPos;
}

void Player::updatePlayerDir()
{
    // PPA3 input processing logic 
    // hasInput = 0;
    char input = mainGameMechsRef->getInput();
    if(input != 0)
    {
        switch(input)
        {                      
            case 'W':
            case 'w':
                if(playerdirection != DOWN)
                {
                    playerdirection = UP;
                    MacUILib_printf("Player direction: UP");
                    hasInput = 1;
                }
                break;
            case 'S':
            case 's':
                if(playerdirection != UP)
                {
                    playerdirection = DOWN;
                    MacUILib_printf("Player direction: DOWN");
                    hasInput = 1;
                }
                break;
            case 'A':
            case 'a':

                if(playerdirection != RIGHT)
                {
                    playerdirection = LEFT;
                    MacUILib_printf("Player direction: LEFT");
                    hasInput = 1;
                }
                break;
            case 'D':
            case 'd':
                if(playerdirection != LEFT)
                {
                    playerdirection = RIGHT;
                    MacUILib_printf("Player direction: RIGHT");
                    hasInput = 1;
                }
                break;
                            
            default:
                break;
        }
        input = 0;
    }
            
}

void Player::movePlayer()
{
    // PPA3 Finite State Machine logic
    int x = playerPos.pos->x;
    int y = playerPos.pos->y;
    if(hasInput != 0)
    {
        switch(playerdirection)
        {
            case UP:
                y = (y - 1 + mainGameMechsRef->getBoardSizeY()) % mainGameMechsRef->getBoardSizeY();
                break;
            case DOWN:
                y = (y + 1) % mainGameMechsRef->getBoardSizeY();
                break;
            case LEFT:
                x = (x - 1 + mainGameMechsRef->getBoardSizeX()) % mainGameMechsRef->getBoardSizeX();
                break;
            case RIGHT:
                x = (x + 1) % mainGameMechsRef->getBoardSizeX();
                break;
        }
        playerPos.setObjPos(x, y, '@');
    }
}   

// More methods to be added