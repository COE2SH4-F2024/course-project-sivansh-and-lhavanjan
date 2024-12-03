#include "objPosArrayList.h"
#include "MacUILib.h"

// Default constructor for objPosArrayList class
objPosArrayList::objPosArrayList() {
    listSize = 0;                          // Initialize list size to 0
    arrayCapacity = ARRAY_MAX_CAP;         // Set initial array capacity
    aList = new objPos[ARRAY_MAX_CAP];     // Allocate memory for the array
}

// Copy constructor for objPosArrayList class
objPosArrayList::objPosArrayList(const objPosArrayList &sList) {
    listSize = sList.listSize;             // Copy list size from source list
    arrayCapacity = sList.arrayCapacity;   // Copy array capacity from source list
    aList = new objPos[ARRAY_MAX_CAP];     // Allocate memory for the array

    // Copy elements from source list to new list
    for (int i = 0; i < listSize; i++) {
        aList[i] = sList.aList[i];
    }
}

// Assignment operator for objPosArrayList class
objPosArrayList &objPosArrayList::operator=(const objPosArrayList &array) {
    if (this != &array) {                  // Check for self-assignment
        this->listSize = array.getSize();  // Copy list size
        // Copy elements from source array to current array
        for (int i = 0; i < this->listSize; i++) {
            this->aList[i] = array.aList[i];
        }
    }
    return *this;                          // Return the current object
}

// Destructor for objPosArrayList class
objPosArrayList::~objPosArrayList() {
    delete[] aList;                        // Deallocate memory for the array
}

// Get the current size of the list
int objPosArrayList::getSize() const {
    return listSize;                       // Return the list size
}

// Insert an element at the head of the list
void objPosArrayList::insertHead(objPos thisPos) {
    if (listSize == arrayCapacity) {       // Check if array is full
        MacUILib_printf("Array is full");  // Print message
        resizeArray();                     // Resize the array
    }

    // Shift elements to the right to make space at the head
    for (int i = listSize; i > 0; i--) {
        aList[i] = aList[i - 1];
    }

    aList[0] = thisPos;                    // Insert new element at the head
    listSize++;                            // Increment list size
}

// Insert an element at the tail of the list
void objPosArrayList::insertTail(objPos thisPos) {
    if (listSize == arrayCapacity) {       // Check if array is full
        MacUILib_printf("Array is full");  // Print message
        resizeArray();                     // Resize the array
    }

    aList[listSize] = thisPos;             // Insert new element at the tail
    listSize++;                            // Increment list size
}

// Remove the element at the head of the list
void objPosArrayList::removeHead() {
    if (listSize == 0) {                   // Check if list is empty
        MacUILib_printf("List is empty");  // Print message
        return;                            // Exit function
    }

    // Shift elements to the left to remove the head
    for (int i = 0; i < listSize - 1; i++) {
        aList[i] = aList[i + 1];
    }

    listSize--;                            // Decrement list size
}

// Remove the element at the tail of the list
void objPosArrayList::removeTail() {
    if (listSize == 0) {                   // Check if list is empty
        MacUILib_printf("List is empty");  // Print message
        return;                            // Exit function
    }

    listSize--;                            // Decrement list size
}

// Get the element at the head of the list
objPos objPosArrayList::getHeadElement() const {
    return aList[0];                       // Return the head element
}

// Get the element at the tail of the list
objPos objPosArrayList::getTailElement() const {
    return aList[listSize - 1];            // Return the tail element
}

// Get the element at a specific index
objPos objPosArrayList::getElement(int index) const {
    if (index < 0 || index >= listSize) {  // Check if index is valid
        MacUILib_printf("Invalid index");  // Print message
        return objPos();                   // Return a default objPos object
    }

    return aList[index];                   // Return the element at the specified index
}

// Resize the array when capacity is reached
void objPosArrayList::resizeArray() {
    int newCapacity = arrayCapacity * 2;   // Double the capacity

    objPos *newArray = new objPos[newCapacity]; // Allocate memory for the new array

    // Copy elements from old array to new array
    for (int i = 0; i < listSize; i++) {
        newArray[i] = aList[i];
    }

    delete[] aList;                        // Deallocate memory for the old array

    aList = newArray;                      // Update the array pointer to the new array
    arrayCapacity = newCapacity;           // Update the capacity
}