#ifndef FOOD_H
#define FOOD_H

#include <cstdlib>
#include <time.h>

#include "objPos.h"
#include "objPosArrayList.h"

#include "GameMechs.h"

using namespace std;

class Food
{
    private:
        // objPos foodPos;
        objPosArrayList* foodBucket; // item bin to hold the food on the board
        int specialFoods; // number of special foods
    public:
        Food();
        ~Food();

        // void generateFood(objPosArrayList* snakeBody);
        void generateFood(objPosArrayList* snakeBody, int totalFoods); // generate the random items on the board from the item bin
        // objPos getFoodPos() const;

        objPosArrayList* getFoodBucket() const; // getter for the item bin

        void clearFood(); // clears the food objects for a reset
};

#endif