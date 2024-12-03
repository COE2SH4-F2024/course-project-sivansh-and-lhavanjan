#ifndef FOOD_H
#define FOOD_H

#include <cstdlib>
#include <time.h>

#include "objPos.h"
#include "objPosArrayList.h"
#include "GameMechs.h"

// Class representing the food in the game
class Food {
private:
    objPosArrayList *foodBucket; // List to store food positions
    int specialFoods;            // Count of special food items

public:
    // Constructor
    Food();

    // Copy constructor
    Food(const Food &other);

    // Assignment operator
    Food &operator=(const Food &other);

    // Destructor
    ~Food();

    // Method to generate food on the board
    void generateFood(objPosArrayList *snakeBody, int totalFoods);

    // Method to get the current food bucket
    objPosArrayList *getFoodBucket() const;

    // Method to clear all food items from the food bucket
    void clearFood();
};

#endif