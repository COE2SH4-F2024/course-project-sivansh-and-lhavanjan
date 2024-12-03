#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "Player.h"
#include "Food.h"

using namespace std;

#define DELAY_CONST 100000 // Constant for delay
#define height 15          // Height of the game board
#define width 30           // Width of the game board

Player *myPlayer; // Pointer to the Player object
GameMechs *myGM;  // Pointer to the GameMechs object
Food *myFood;     // Pointer to the Food object

// Function declarations
void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);

int main(void)
{
    srand(time(0)); // Seed the random number generator
    Initialize();   // Initialize game components

    // Main game loop
    while (myGM->getExitFlagStatus() == false)
    {
        GetInput();   // Get user input
        RunLogic();   // Process game logic
        DrawScreen(); // Render the game screen
        LoopDelay();  // Delay for game loop timing
    }

    CleanUp(); // Clean up resources
}

void Initialize(void)
{
    MacUILib_init();        // Initialize the MacUILib
    MacUILib_clearScreen(); // Clear the screen

    myGM = new GameMechs(); // Create a new GameMechs object
    myFood = new Food();    // Create a new Food object
    myPlayer = new Player(myGM, myFood, 1); // Create a new Player object with initial length 1

    myFood->generateFood(myPlayer->getPlayerPos(), 5); // Generate initial food items
}

void GetInput(void)
{
    char input = myGM->getInput(); // Get input from GameMechs
    myGM->setInput(input);         // Set the input in GameMechs
}

void RunLogic(void)
{
    char input = myGM->getInput(); // Get the current input

    // Check for exit command
    if (input == '$')
    {
        myGM->setExitTrue(); // Set exit flag
        MacUILib_printf("Exited by command.");
        return;
    }

    // Increase speed command
    if (input == '>')
    {
        myGM->setSpeed(myGM->getSpeed() + 1); // Increase speed
        myPlayer->speedControl();             // Control player speed
    }

    // Decrease speed command
    if (input == '<')
    {
        myGM->setSpeed(myGM->getSpeed() - 1); // Decrease speed
        myPlayer->speedControl();             // Control player speed
    }

    // Trigger lose flag command
    if (input == '-')
    {
        myGM->setLoseFlag(); // Set lose flag
        myGM->setExitTrue(); // Set exit flag
        MacUILib_printf("Debug: Lose flag triggered.");
        return;
    }

    myPlayer->updatePlayerDir(); // Update player direction
    myPlayer->movePlayer();      // Move player

    // Clear input if it matches specific commands
    if (input == 0 || input == '$' || input == 'R' || input == 'r' || input == '>' || input == '<' || input == '-')
    {
        myGM->clearInput(); // Clear the input
    }
}

void DrawScreen(void)
{
    MacUILib_clearScreen(); // Clear the screen

    objPosArrayList *snakeBody = myPlayer->getPlayerPos(); // Get player position list
    objPosArrayList *foodBucket = myFood->getFoodBucket(); // Get food bucket

    // Iterate over each position on the game board
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            bool isSnakeBody = false; // Flag to check if position is part of the snake
            bool isFood = false;      // Flag to check if position is food

            // Check if current position is part of the snake
            for (int i = 0; i < snakeBody->getSize(); i++)
            {
                if (snakeBody->getElement(i).pos->x == x && snakeBody->getElement(i).pos->y == y)
                {
                    MacUILib_printf("%c", snakeBody->getElement(i).getSymbol()); // Print snake symbol
                    isSnakeBody = true;
                    break;
                }
            }

            // Check if current position is food
            if (!isSnakeBody)
            {
                for (int i = 0; i < foodBucket->getSize(); i++)
                {
                    objPos food = foodBucket->getElement(i);

                    if (food.pos->x == x && food.pos->y == y)
                    {
                        MacUILib_printf("%c", food.getSymbol()); // Print food symbol
                        isFood = true;
                        break;
                    }
                }
            }

            // Print border or empty space
            if (!isSnakeBody && !isFood)
            {
                if (y == 0 || y == height - 1 || x == 0 || x == width - 1)
                {
                    MacUILib_printf("#"); // Print border
                }
                else
                {
                    MacUILib_printf(" "); // Print empty space
                }
            }
        }
        MacUILib_printf("\n"); // New line after each row
    }

    // Print debug information
    MacUILib_printf("Debug: Score incremented. Current Score: %d\n", myGM->getScore());
    MacUILib_printf("Speed: %d, Delay: %d\n", myGM->getSpeed(), myGM->getDelayAmount());
}

void LoopDelay(void)
{
    MacUILib_Delay(myGM->getDelayAmount()); // Delay for game loop timing
}

void CleanUp(void)
{
    MacUILib_clearScreen(); // Clear the screen

    // Check game status and print appropriate message
    if (myGM->getLoseFlagStatus())
    {
        MacUILib_printf("Game over. You lost.\n");
    }
    else if (myGM->getExitFlagStatus())
    {
        MacUILib_printf("Game exited by command.\n");
    }
    else
    {
        MacUILib_printf("You won!\n");
    }

    MacUILib_printf("Final Score: %d\n", myGM->getScore()); // Print final score

    // Deallocate resources
    delete myPlayer;
    delete myGM;
    delete myFood;

    MacUILib_uninit(); // Uninitialize the MacUILib
}
