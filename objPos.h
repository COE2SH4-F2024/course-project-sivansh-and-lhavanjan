#ifndef OBJPOS_H
#define OBJPOS_H

// Structure to represent a position with x and y coordinates
typedef struct {
    int x; // x coordinate
    int y; // y coordinate
} Pos;

// Class to represent an object with a position and a symbol
class objPos {
public:
    Pos *pos;    // Pointer to a Pos structure
    char symbol; // Symbol representing the object

    // Default constructor
    objPos();

    // Parameterized constructor
    objPos(int xPos, int yPos, char sym);

    // Copy constructor
    objPos(const objPos &a);

    // Assignment operator
    objPos &operator=(const objPos &a);

    // Destructor
    ~objPos();

    // Set the position and symbol using another objPos object
    void setObjPos(objPos o);

    // Set the position and symbol using individual values
    void setObjPos(int xPos, int yPos, char sym);

    // Get the current position and symbol as an objPos object
    objPos getObjPos() const;

    // Get the current symbol
    char getSymbol() const;

    // Get the symbol if the position matches the reference position
    char getSymbolIfPosEqual(const objPos *refPos) const;

    // Check if the position matches the reference position
    bool isPosEqual(const objPos *refPos) const;
};

#endif