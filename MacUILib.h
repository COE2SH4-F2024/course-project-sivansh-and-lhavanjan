#ifndef MAC_UI_LIB
#define MAC_UI_LIB

#include <stdio.h>
#include <stdlib.h>

// Function to initialize the library
void MacUILib_init(void);

// Function to initialize the library with synchronous settings
void MacUILib_init_sync(void);

// Function to delay execution for a specified number of microseconds
void MacUILib_Delay(int usec);

// Function to check if a keyboard character is available
int MacUILib_hasChar(void);

// Function to get a character from the keyboard
char MacUILib_getChar(void);

// Function to clear the console screen
void MacUILib_clearScreen(void);

// Function to uninitialize the library and prompt for shutdown
void MacUILib_uninit(void);

// Typedef for a function pointer to a print function
typedef int (*print_ptr)(const char *, ...);

// External declaration of the print function pointer
extern print_ptr MacUILib_printf;

#endif
