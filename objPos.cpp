#include "objPos.h"

// Default constructor for objPos class
objPos::objPos() {
    pos = new Pos;  // Allocate memory for Pos object
    pos->x = 0;     // Initialize x coordinate to 0
    pos->y = 0;     // Initialize y coordinate to 0
    symbol = 0;     // Initialize symbol to 0
}

// Parameterized constructor for objPos class
objPos::objPos(int xPos, int yPos, char sym) {
    pos = new Pos;  // Allocate memory for Pos object
    pos->x = xPos;  // Set x coordinate to xPos
    pos->y = yPos;  // Set y coordinate to yPos
    symbol = sym;   // Set symbol to sym
}

// Copy constructor for objPos class
objPos::objPos(const objPos &a) {
    pos = new Pos;  // Allocate memory for Pos object
    pos->x = a.pos->x;  // Copy x coordinate from object a
    pos->y = a.pos->y;  // Copy y coordinate from object a
    symbol = a.symbol;  // Copy symbol from object a
}

// Assignment operator for objPos class
objPos &objPos::operator=(const objPos &a) {
    if (this != &a) {  // Check for self-assignment
        pos = new Pos;  // Allocate memory for Pos object
        this->pos->x = a.pos->x;  // Copy x coordinate from object a
        this->pos->y = a.pos->y;  // Copy y coordinate from object a
        this->symbol = a.symbol;  // Copy symbol from object a
    }
    return *this;  // Return the current object
}

// Destructor for objPos class
objPos::~objPos() {
    delete pos;  // Deallocate memory for Pos object
}

// Set the position and symbol using another objPos object
void objPos::setObjPos(objPos o) {
    pos->x = o.pos->x;  // Set x coordinate from object o
    pos->y = o.pos->y;  // Set y coordinate from object o
    symbol = o.symbol;  // Set symbol from object o
}

// Set the position and symbol using individual values
void objPos::setObjPos(int xPos, int yPos, char sym) {
    pos->x = xPos;  // Set x coordinate to xPos
    pos->y = yPos;  // Set y coordinate to yPos
    symbol = sym;   // Set symbol to sym
}

// Get the current position and symbol as an objPos object
objPos objPos::getObjPos() const {
    objPos returnPos;  // Create a new objPos object
    returnPos.pos->x = pos->x;  // Copy x coordinate
    returnPos.pos->y = pos->y;  // Copy y coordinate
    returnPos.symbol = symbol;  // Copy symbol

    return returnPos;  // Return the new objPos object
}

// Get the current symbol
char objPos::getSymbol() const {
    return symbol;  // Return the symbol
}

// Check if the position is equal to another objPos object
bool objPos::isPosEqual(const objPos *refPos) const {
    return (refPos->pos->x == pos->x && refPos->pos->y == pos->y);  // Compare coordinates
}

// Get the symbol if the position is equal to another objPos object
char objPos::getSymbolIfPosEqual(const objPos *refPos) const {
    if (isPosEqual(refPos))  // Check if positions are equal
        return symbol;  // Return the symbol if equal
    else
        return 0;  // Return 0 if not equal
}
