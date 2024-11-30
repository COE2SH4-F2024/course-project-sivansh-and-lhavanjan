#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "Player.h"
#include "Food.h"

using namespace std;

#define DELAY_CONST 100000
#define height 15
#define width 30

Player *myPlayer; // Global pointer meant to instantiate a player object on the heap
GameMechs *myGM;
Food *myFood;


void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);



int main(void)
{

    Initialize();

    while(myGM->getExitFlagStatus() == false)  
    {
        GetInput();
        RunLogic();
        DrawScreen();
        LoopDelay();
    }

    CleanUp();

}


void Initialize(void)
{
    MacUILib_init();
    MacUILib_clearScreen();

    myGM = new GameMechs();
    // myPlayer = new Player(myGM);
    myPlayer = new Player(myGM, 3);
    myFood = new Food();

    // myFood->generateFood(myPlayer->getPlayerPos());
}

void GetInput(void)
{
    char input = myGM->getInput();
    myGM->setInput(input);
}

void RunLogic(void)
{
    char input = myGM->getInput();
    if(input == '$')
    {
        myGM->setExitTrue();
        MacUILib_printf("Exited by command.");
        return;
    }

    if(input == '+')
    {
        myGM->incrementScore();
    }

    if(input == '>')
    {
        myGM->setSpeed(myGM->getSpeed() + 1);
        myPlayer->speedControl();
    }

    if(input == '<')
    {
        myGM->setSpeed(myGM->getSpeed() - 1);
        myPlayer->speedControl();
    }

    /* if(input == 'R' || input == 'r')
    {
        myFood->generateFood(myPlayer->getPlayerPos());
        MacUILib_printf("Debug: Food generated at [%d, %d]\n", myFood->getFoodPos().pos->x, myFood->getFoodPos().pos->y);
    } */

    if(input == '-')
    {
        myGM->setLoseFlag();
        myGM->setExitTrue();
        MacUILib_printf("Debug: Lose flag triggered.");
        return;
    }

    myPlayer->updatePlayerDir();
    myPlayer->movePlayer();
    
    if(input == 0 || input == '$' || input == '+' || input == 'R' || input == 'r' || input == '>' || input == '<' || input == '-')
    {
        myGM->clearInput();
    }
}

void DrawScreen(void)
{
    MacUILib_clearScreen();

    // objPos playerPos = myPlayer->getPlayerPos();
    objPosArrayList* snakeBody = myPlayer->getPlayerPos();
    objPos foodPosition = myFood->getFoodPos();

    // MacUILib_printf("Player [x, y, symbol] = [%d, %d, %c]\n", playerPos.pos->x, playerPos.pos->y, playerPos.symbol);

    /* for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; ++x)
        {
            if (y == 0 || y == height - 1 || x == 0 || x == width - 1)
                MacUILib_printf("#");
            else
            {
                if (x == playerPos.pos->x && y == playerPos.pos->y)
                {
                    MacUILib_printf("%c", playerPos.getSymbol());
                }
                else if(x == foodPosition.pos->x && y == foodPosition.pos->y)
                {
                    MacUILib_printf("%c", foodPosition.getSymbol());
                }
                else
                {
                    MacUILib_printf(" ");
                }
            }
        }
        MacUILib_printf("\n");
    } */

   for(int y = 0; y < height; y++)
   {
        for(int x = 0; x < width; x++)
        {
            bool isSnakeBody = false;

            for(int i = 0; i < snakeBody->getSize(); i++)
            {
                if(snakeBody->getElement(i).pos->x == x && snakeBody->getElement(i).pos->y == y)
                {
                    MacUILib_printf("%c", snakeBody->getElement(i).getSymbol());
                    isSnakeBody = true;
                    break;
                }
            }

            if(!isSnakeBody)
            {
                if(y == 0 || y == height - 1 || x == 0 || x == width - 1)
                {
                    MacUILib_printf("#");
                }
                else if (x == foodPosition.pos->x && y == foodPosition.pos->y)
                {
                    
                    MacUILib_printf("%c", foodPosition.getSymbol());
                }
                else
                {
                    MacUILib_printf(" ");
                }
            }
        }
        MacUILib_printf("\n");
   }

    MacUILib_printf("Debug: Score incremented. Current Score: %d\n", myGM->getScore());
    MacUILib_printf("Debug: Food generated at [%d, %d]\n", myFood->getFoodPos().pos->x, myFood->getFoodPos().pos->y);
    MacUILib_printf("Speed: %d, Delay: %d", myGM->getSpeed(), myGM->getDelayAmount());
}

void LoopDelay(void)
{
    MacUILib_Delay(myGM->getDelayAmount()); // 0.1s delay
}


void CleanUp(void)
{
    MacUILib_clearScreen();    

    if(myGM->getLoseFlagStatus())
    {
        MacUILib_printf("Game over. You lost.\n");
    }
    else if(myGM->getExitFlagStatus())
    {
        MacUILib_printf("Game exited by command.\n");
    }
    else
    {
        MacUILib_printf("You won!\n");
    }

    MacUILib_printf("Final Score: %d\n", myGM->getScore());
    
    delete myPlayer;
    delete myGM;
    delete myFood; 

    MacUILib_uninit();
}
