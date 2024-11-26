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

}

objPos Food::getFoodPos() const
{
    return foodPos;
}