#include "Food.h"
#include "MacUILib.h"

/*Food::Food()
{
    foodPos.setObjPos(10, 10, 'o');
}*/

Food::Food()
{
    foodBucket = new objPosArrayList(); // initialize space for the bucket on the heap
    specialFoods = 0;
}

Food::~Food()
{
    delete foodBucket; // deallocates the space initialized at the end of the program 
}

/*void Food::generateFood(objPosArrayList* snakeBody)
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
}*/    

void Food::generateFood(objPosArrayList* snakeBody, int totalFoods)
{
    // srand(time(0));

    clearFood();
    int boardWidth = 28;
    int boardHeight = 13;
    int randX;
    int randY;
    bool validPosition;

    for(int i = 0; i < totalFoods; i++)
    {
        validPosition = false;
        while(!validPosition)
        {
            randX = (rand() % boardWidth) + 1;
            randY = (rand() % boardHeight) + 1;

            validPosition = true;

            for(int j = 0; j < snakeBody->getSize(); j++)
            {
                if(snakeBody->getElement(i).pos->x == randX && snakeBody->getElement(i).pos->y == randY)
                {
                    validPosition = false;
                    break;
                }
            }
        }

        char symbol;
        if(i < 2) // first two foods in the bucket are special foods
        {
            symbol = '?'; // '?' to denote special foods, kinda like mario kart
        }
        else
        {
            symbol = 'o'; // 'o' to denote regular food
        }

        foodBucket->insertTail(objPos(randX, randY, symbol));
    }
}    

/*objPos Food::getFoodPos() const
{
    return foodPos;
}*/

objPosArrayList* Food::getFoodBucket() const
{
    return foodBucket;
}

void Food::clearFood()
{
    while(foodBucket->getSize() > 0)
    {
        foodBucket->removeHead();
    }
}