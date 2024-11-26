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
    myPlayer = new Player(myGM);
    myFood = new Food();
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
        // MacUILib_printf("Debug: Score incremented. Current Score: %d\n", myGM->getScore());
    }

    if(input == '-')
    {
        myGM->setLoseFlag();
        myGM->setExitTrue();
        MacUILib_printf("Debug: Lose flag triggered.");
        return;
    }
    myPlayer->updatePlayerDir();
    myPlayer->movePlayer();
    if(input == 0 || input == '$' || input == '+')
    {
        myGM->clearInput();
    }
}

void DrawScreen(void)
{
    MacUILib_clearScreen();

    objPos playerPos = myPlayer->getPlayerPos();
    objPos foodPosition = myFood->getFoodPos();

    MacUILib_printf("Player [x, y, symbol] = [%d, %d, %c]\n", playerPos.pos->x, playerPos.pos->y, playerPos.symbol);

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; ++x)
        {
            if (y == 0 || y == height - 1 || x == 0 || x == width - 1)
                MacUILib_printf("#");
            else
            {
                objPos charA(5, 3, 'A');
                objPos charB(8, 6, 'B');

                if (x == charA.pos->x && y == charA.pos->y)
                {
                    MacUILib_printf("%c", charA.getSymbol());
                }
                else if (x == charB.pos->x && y == charB.pos->y)
                {
                    MacUILib_printf("%c", charB.getSymbol());
                }
                else if (x == playerPos.pos->x && y == playerPos.pos->y)
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
    }

    MacUILib_printf("Debug: Score incremented. Current Score: %d\n", myGM->getScore());
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
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

    MacUILib_uninit();
}
