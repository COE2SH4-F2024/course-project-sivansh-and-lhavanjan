#include "Food.h"
#include "MacUILib.h"

Food::Food()
{
    foodPos.setObjPos(10, 10, 'o');
}

Food::~Food()
{

}

// void Food::generateFood(objPos blockoff)
void Food::generateFood(objPosArrayList* snakeBody)
{
    // srand(time(0));

    int boardWidth = 28;
    int boardHeight = 13;

    int randX;
    int randY;
    bool validPosition = false;
    int iterations = 0;

    MacUILib_printf("Debug: Starting food generation\n");

    while(!validPosition)
    {
        randX = (rand() % boardWidth) + 1;
        randY = (rand() % boardHeight) + 1;

        validPosition = true;

        for(int i = 0; i < snakeBody->getSize(); i++)
        {
            if(snakeBody->getElement(i).pos->x == randX && snakeBody->getElement(i).pos->y == randY)
            {
                validPosition = false;
                break;
            }
        }

        iterations++;
        if(iterations > 1000)
        {
            randX = 0;
            randY = 0;
            validPosition = true;
            MacUILib_printf("Debug: Too many iterations, defaulting food position to [%d, %d]\n", randX, randY);
        }
    }
    foodPos.setObjPos(randX, randY, 'o');
    MacUILib_printf("Debug: Food placed at [%d, %d]\n", randX, randY);
}    

objPos Food::getFoodPos() const
{
    return foodPos;
}