#include "Food.h"
#include "MacUILib.h"

// Constructor for the Food class
Food::Food() {
    // Initialize the food bucket as a new objPosArrayList
    foodBucket = new objPosArrayList();
    // Initialize the count of special foods
    specialFoods = 0;
}

// Copy constructor for the Food class
Food::Food(const Food &other) {
    // Create a new objPosArrayList by copying the other food bucket
    foodBucket = new objPosArrayList(*other.foodBucket);
    // Copy the count of special foods
    specialFoods = other.specialFoods;
}

// Assignment operator for the Food class
Food &Food::operator=(const Food &other) {
    if (this != &other) { // Check for self-assignment
        // Create a new objPosArrayList by copying the other food bucket
        foodBucket = new objPosArrayList(*other.foodBucket);
        // Copy the count of special foods
        specialFoods = other.specialFoods;
    }
    return *this; // Return the current object
}

// Destructor for the Food class
Food::~Food() {
    // Delete the food bucket to free memory
    delete foodBucket;
}

// Method to generate food on the board
void Food::generateFood(objPosArrayList *snakeBody, int totalFoods) {
    // Clear any existing food before generating new ones
    clearFood();
    // Define the board dimensions
    int boardWidth = 28;
    int boardHeight = 13;
    int randX;
    int randY;
    bool validPosition;

    // Loop to generate the specified number of food items
    for (int i = 0; i < totalFoods; i++) {
        validPosition = false;
        // Find a valid position for the food
        while (!validPosition) {
            // Generate random coordinates within the board
            randX = (rand() % boardWidth) + 1;
            randY = (rand() % boardHeight) + 1;

            validPosition = true;

            // Check if the generated position overlaps with the snake's body
            for (int j = 0; j < snakeBody->getSize(); j++) {
                if (snakeBody->getElement(i).pos->x == randX && snakeBody->getElement(i).pos->y == randY) {
                    validPosition = false;
                    break;
                }
            }
        }

        char symbol;
        // Assign a special symbol for the first two foods
        if (i < 2) {
            symbol = '?';
        } else {
            symbol = 'o';
        }

        // Insert the new food item into the food bucket
        foodBucket->insertTail(objPos(randX, randY, symbol));
    }
}

// Method to get the current food bucket
objPosArrayList *Food::getFoodBucket() const {
    return foodBucket;
}

// Method to clear all food items from the food bucket
void Food::clearFood() {
    // Remove all elements from the food bucket
    while (foodBucket->getSize() > 0) {
        foodBucket->removeHead();
    }
}