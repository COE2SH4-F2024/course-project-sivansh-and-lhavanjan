#include "Player.h"
#include "MacUILib.h"

int hasInput = 0;

/* Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    playerdirection = STOP;

    // more actions to be included
    // playerPos.pos->x = mainGameMechsRef->getBoardSizeX() / 2;
    // playerPos.pos->y = mainGameMechsRef->getBoardSizeY() / 2;
    // playerPos.symbol = '@';

    playerPosList = new objPosArrayList();

    int startX = mainGameMechsRef->getBoardSizeX() / 2;
    int startY = mainGameMechsRef->getBoardSizeY() / 2;

    objPos headPosition(startX, startY, '*');

    playerPosList->insertHead(headPosition);
} */

Player::Player(GameMechs* thisGMRef, int initialLength)
{
    mainGameMechsRef = thisGMRef;
    playerdirection = STOP;

    // more actions to be included
    // playerPos.pos->x = mainGameMechsRef->getBoardSizeX() / 2;
    // playerPos.pos->y = mainGameMechsRef->getBoardSizeY() / 2;
    // playerPos.symbol = '@';

    playerPosList = new objPosArrayList();

    int startX = mainGameMechsRef->getBoardSizeX() / 2;
    int startY = mainGameMechsRef->getBoardSizeY() / 2;

    for(int i = 0; i < initialLength; i++)
    {
        objPos segment(startX - i, startY, '*');
        playerPosList->insertHead(segment);
    }
    // objPos headPosition(startX, startY, '*');

    // playerPosList->insertHead(headPosition);
}

Player::~Player()
{
    // delete any heap members here
}

objPosArrayList* Player::getPlayerPos() const
{
    return playerPosList;
}
/* objPos Player::getPlayerPos() const
{
    // return the reference to the playerPos arrray list
    // return playerPos;
    return playerPosList->getHeadElement();
} */

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
    /* int x = playerPos.pos->x;
    int y = playerPos.pos->y; */

    int maxWidth = (mainGameMechsRef->getBoardSizeX() - 1);
    int maxHeight = (mainGameMechsRef->getBoardSizeY() - 1);

    if(hasInput != 0)
    {
        int newX = playerPosList->getHeadElement().pos->x;
        int newY = playerPosList->getHeadElement().pos->y;

        switch(playerdirection)
        {
            case UP:
                newY = (newY - 1 + maxHeight) % maxHeight;
                if (newY== 0)
                {
                    newY = maxHeight - 1;
                }
                break;
            case DOWN:
                newY = (newY + 1) % maxHeight;
                if (newY == 0)
                {
                    newY = 1;
                }
                break;
            case LEFT:
                newX = (newX - 1 + maxWidth) % maxWidth;
                if (newX == 0)
                {
                    newX = maxWidth - 1;
                }
                break;
            case RIGHT:
                newX = (newX + 1) % maxWidth;
                if (newX == 0)
                {
                    newX = 1;
                }
                break;
        }
        objPos newHeadPosition(newX, newY, '*');
        playerPosList->insertHead(newHeadPosition);
        playerPosList->removeTail();

        /* switch(playerdirection)
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
        playerPos.setObjPos(x, y, '@'); */
    }
}   

// More methods to be added

void Player::speedControl()
{
    switch(mainGameMechsRef->getSpeed())
    {
        case 1:
            mainGameMechsRef->setDelayAmount(150000);
            break;
        case 2:
            mainGameMechsRef->setDelayAmount(125000);
            break;
        case 3:
            mainGameMechsRef->setDelayAmount(100000);
            break;
        case 4:
            mainGameMechsRef->setDelayAmount(75000);
            break;
        case 5:
            mainGameMechsRef->setDelayAmount(50000);
            break;
        default:
            mainGameMechsRef->setDelayAmount(100000);
            break;
    }

    MacUILib_printf("Speed: %d, Delay: %d", mainGameMechsRef->getSpeed(), mainGameMechsRef->getDelayAmount());
}