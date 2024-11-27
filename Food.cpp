#include "Food.h"
#include "MacUILib.h"

Food::Food()
{
    foodPos.setObjPos(10, 10, 'o');
}

Food::~Food()
{

}

void Food::generateFood(objPos blockoff)
{
    srand(time(0));

    int boardWidth = 28;
    int boardHeight = 13;

    int randX;
    int randY;
    bool validPosition = false;

    while(!validPosition)
    {
        randX = (rand() % boardWidth) + 1;
        randY = (rand() % boardHeight) + 1;

        if(randX != blockoff.pos->x && randY != blockoff.pos->y)
        {
            validPosition = true;
        }

    }

    foodPos.setObjPos(randX, randY, 'o');
}

objPos Food::getFoodPos() const
{
    return foodPos;
}