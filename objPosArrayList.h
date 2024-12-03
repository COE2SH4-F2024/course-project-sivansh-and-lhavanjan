#ifndef OBJPOS_ARRAYLIST_H
#define OBJPOS_ARRAYLIST_H

#define ARRAY_MAX_CAP 200  // Maximum initial capacity of the array

#include "objPos.h"  // Include the objPos class definition

// Class to manage a dynamic array list of objPos objects
class objPosArrayList {
private:
    objPos* aList;          // Pointer to the dynamic array of objPos objects
    int listSize;           // Current number of elements in the list
    int arrayCapacity;      // Current capacity of the array

public:
    objPosArrayList();                                      // Default constructor
    objPosArrayList(const objPosArrayList& slist);          // Copy constructor
    ~objPosArrayList();                                     // Destructor
    objPosArrayList& operator=(const objPosArrayList& array); // Assignment operator

    int getSize() const;                                    // Get the current size of the list
    void insertHead(objPos thisPos);                        // Insert an element at the head of the list
    void insertTail(objPos thisPos);                        // Insert an element at the tail of the list
    void removeHead();                                      // Remove the element at the head of the list
    void removeTail();                                      // Remove the element at the tail of the list

    objPos getHeadElement() const;                          // Get the element at the head of the list
    objPos getTailElement() const;                          // Get the element at the tail of the list
    objPos getElement(int index) const;                     // Get the element at a specific index
    void resizeArray();                                     // Resize the array when capacity is reached
};

#endif