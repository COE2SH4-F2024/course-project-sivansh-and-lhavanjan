#include "Player.h"
#include "MacUILib.h"

int hasInput = 0;

Player::Player(GameMechs *thisGMRef)
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
    if (input != 0)
    {
        switch (input)
        {
        case 'W':
        case 'w':
            if (playerdirection != DOWN)
            {
                playerdirection = UP;
                MacUILib_printf("Player direction: UP");
                hasInput = 1;
            }
            break;
        case 'S':
        case 's':
            if (playerdirection != UP)
            {
                playerdirection = DOWN;
                MacUILib_printf("Player direction: DOWN");
                hasInput = 1;
            }
            break;
        case 'A':
        case 'a':

            if (playerdirection != RIGHT)
            {
                playerdirection = LEFT;
                MacUILib_printf("Player direction: LEFT");
                hasInput = 1;
            }
            break;
        case 'D':
        case 'd':
            if (playerdirection != LEFT)
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

    int maxWidth = (mainGameMechsRef->getBoardSizeX() - 1);
    int maxHeight = (mainGameMechsRef->getBoardSizeY() - 1);

    if (hasInput != 0)
    {
        switch (playerdirection)
        {
        case UP:
            y = (y - 1 + maxHeight) % maxHeight;
            if (y == 0)
            {
                y = maxHeight - 1;
            }
            break;
        case DOWN:
            y = (y + 1) % maxHeight;
            if (y == 0)
            {
                y = 1;
            }
            break;
        case LEFT:
            x = (x - 1 + maxWidth) % maxWidth;
            if (x == 0)
            {
                x = maxWidth - 1;
            }
            break;
        case RIGHT:
            x = (x + 1) % maxWidth;
            if (x == 0)
            {
                x = 1;
            }
            break;
        }
        playerPos.setObjPos(x, y, '@');
    }
}

// More methods to be added

void Player::speedControl()
{
    switch (mainGameMechsRef->getSpeed())
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