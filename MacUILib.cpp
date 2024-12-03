#include "MacUILib.h"

// Function pointer for printing, set based on platform
print_ptr MacUILib_printf;

#ifdef WINDOWS

#include <conio.h>
#include <windows.h>

// Initialize the library for Windows platform
void MacUILib_init(void) {
    MacUILib_printf = &printf; // Set the print function to standard printf
}

// Initialize the library for Windows platform with synchronous settings
void MacUILib_init_sync(void) {
    MacUILib_printf = &printf; // Set the print function to standard printf
}

// Delay execution for a specified number of microseconds
void MacUILib_Delay(int usec) {
    Sleep(usec / 1000); // Convert microseconds to milliseconds for Sleep
}

// Check if a keyboard character is available
int MacUILib_hasChar(void) {
    return _kbhit(); // Return non-zero if a key is available
}

// Get a character from the keyboard
char MacUILib_getChar(void) {
    return _getch(); // Return the character read from the keyboard
}

// Clear the console screen
void MacUILib_clearScreen(void) {
    system("cls"); // Use system call to clear the screen
}

// Uninitialize the library and prompt for shutdown
void MacUILib_uninit(void) {
    MacUILib_printf("\nPress ENTER to Shut Down\n"); // Prompt user
    getchar(); // Wait for user input
}

#endif

#ifdef POSIX

#include <ncurses.h>
#include <unistd.h>

// Initialize the library for POSIX platform
void MacUILib_init(void) {
    MacUILib_printf = &printw; // Set the print function to ncurses printw

    initscr(); // Initialize the ncurses screen
    noecho(); // Disable echoing of typed characters
    cbreak(); // Disable line buffering
    nodelay(stdscr, TRUE); // Set getch to be non-blocking
    curs_set(0); // Hide the cursor
}

// Initialize the library for POSIX platform with synchronous settings
void MacUILib_init_sync(void) {
    MacUILib_printf = &printw; // Set the print function to ncurses printw

    initscr(); // Initialize the ncurses screen
    noecho(); // Disable echoing of typed characters
    curs_set(0); // Hide the cursor
}

// Delay execution for a specified number of microseconds
void MacUILib_Delay(int usec) {
    refresh(); // Refresh the screen to apply changes
    usleep(usec); // Sleep for the specified microseconds
}

// Check if a keyboard character is available
int MacUILib_hasChar() {
    char ch = getch(); // Get a character from the keyboard
    if (ch == ERR) {
        return 0; // Return 0 if no character is available
    } else {
        ungetch(ch); // Put the character back into the input buffer
        return 1; // Return 1 if a character is available
    }
}

// Get a character from the keyboard
char MacUILib_getChar(void) {
    return getch(); // Return the character read from the keyboard
}

// Clear the console screen
void MacUILib_clearScreen(void) {
    clear(); // Clear the ncurses screen
}

// Uninitialize the library and prompt for shutdown
void MacUILib_uninit(void) {
    MacUILib_printf("\nPress ENTER to Shut Down\n"); // Prompt user
    refresh(); // Refresh the screen to apply changes
    getchar(); // Wait for user input
    endwin(); // End ncurses mode
}

#endif
