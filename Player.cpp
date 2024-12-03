#include "Player.h"
#include "MacUILib.h"

int hasInput = 0;

Player::Player(GameMechs *thisGMRef, Food *thisFoodRef, int initialLength)
{
    mainGameMechsRef = thisGMRef;
    foodRef = thisFoodRef;
    playerdirection = STOP;

    // more actions to be included

    playerPosList = new objPosArrayList();

    int startX = mainGameMechsRef->getBoardSizeX() / 2;
    int startY = mainGameMechsRef->getBoardSizeY() / 2;

    for (int i = 0; i < initialLength; i++)
    {
        objPos segment(startX - i, startY, '@');
        playerPosList->insertHead(segment);
    }
}

Player::Player(const Player& a)
{
    mainGameMechsRef = a.mainGameMechsRef;
    foodRef = a.foodRef;
    playerdirection = a.playerdirection;

    playerPosList = new objPosArrayList(*a.playerPosList);
}

Player& Player::operator=(const Player& a)
{
    if(this != &a)
    {
        mainGameMechsRef = a.mainGameMechsRef;
        foodRef = a.foodRef;
        playerdirection = a.playerdirection;

        playerPosList = new objPosArrayList(*a.playerPosList);
    }
    return *this;
} 

Player::~Player()
{
    // delete any heap members here
    delete playerPosList;
}


objPosArrayList *Player::getPlayerPos() const
{
    return playerPosList;
}

void Player::updatePlayerDir()
{
    // PPA3 input processing logic
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
                MacUILib_printf("Player direction: UP\n");
                hasInput = 1;
            }
            break;
        case 'S':
        case 's':
            if (playerdirection != UP)
            {
                playerdirection = DOWN;
                MacUILib_printf("Player direction: DOWN\n");
                hasInput = 1;
            }
            break;
        case 'A':
        case 'a':

            if (playerdirection != RIGHT)
            {
                playerdirection = LEFT;
                MacUILib_printf("Player direction: LEFT\n");
                hasInput = 1;
            }
            break;
        case 'D':
        case 'd':
            if (playerdirection != LEFT)
            {
                playerdirection = RIGHT;
                MacUILib_printf("Player direction: RIGHT\n");
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

    int maxWidth = (mainGameMechsRef->getBoardSizeX() - 1);
    int maxHeight = (mainGameMechsRef->getBoardSizeY() - 1);

    if (hasInput != 0)
    {
        int newX = playerPosList->getHeadElement().pos->x;
        int newY = playerPosList->getHeadElement().pos->y;

        switch (playerdirection)
        {
        case UP:
            newY = (newY - 1 + maxHeight) % maxHeight;
            if (newY == 0)
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

        // collision check
        if(checkSelfCollision())
        {
            mainGameMechsRef->setLoseFlag();
            mainGameMechsRef->setExitTrue();
            return;
        }

        if(checkFoodConsumption(foodRef))
        {
            objPosArrayList* foodBucket = foodRef->getFoodBucket();
            objPos headPosition = objPos(newX, newY, '@');

            for(int i = 0; i < foodBucket->getSize(); i++)
            {
                objPos food = foodBucket->getElement(i);
                if (headPosition.pos->x == food.pos->x && headPosition.pos->y == food.pos->y)
                {
                    applySpecialFoodEffect(food.getSymbol());
                    foodBucket->removeHead();
                    break;
                }
            }
            increasePlayerLength(newX, newY);
            foodRef->generateFood(playerPosList, 5);
        }
        else
        {
            increasePlayerLength(newX, newY);
            playerPosList->removeTail();
        }
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

bool Player::checkFoodConsumption(Food* foodRef)
{
    objPos headPosition = playerPosList->getHeadElement();
    objPosArrayList* foodBucket = foodRef->getFoodBucket();

    for(int i = 0; i < foodBucket->getSize(); i++)
    {
        objPos food = foodBucket->getElement(i);
        if (headPosition.pos->x == food.pos->x && headPosition.pos->y == food.pos->y)
        {
            applySpecialFoodEffect(food.getSymbol());
            foodBucket->removeHead();
            return true;
        }
    }

    return false;
}

void Player::increasePlayerLength(int newX, int newY)
{
    objPos newSegment(newX, newY, '@');
    playerPosList->insertHead(newSegment);
}

bool Player::checkSelfCollision()
{
    if(playerPosList->getSize()>1)
    {    
        int headX = playerPosList->getHeadElement().pos->x;
        int headY = playerPosList->getHeadElement().pos->y;

        for (int i = 1; i < playerPosList->getSize(); i++)
        {
            int bodyX=playerPosList->getElement(i).pos->x;
            int bodyY=playerPosList->getElement(i).pos->y;
            
            if (headX==bodyX && headY==bodyY)
            {
                return true;
            }
        }
    }
    return false;
}

void Player::applySpecialFoodEffect(char foodSymbol)
{
    switch(foodSymbol)
    {
    case '?':
        mainGameMechsRef->incrementScore(10);
        break;
    case 'o':
        mainGameMechsRef->incrementScore(1);
        break;
    default:
        break;
    }
}