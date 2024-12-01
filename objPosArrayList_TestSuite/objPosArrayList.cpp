#include "objPosArrayList.h"
#include <iostream>

using namespace std;

// Check lecture contents on general purpose array list construction, 
// and modify it to support objPos array list construction.

objPosArrayList::objPosArrayList() // Default constructor
{
    listSize = 0;
    arrayCapacity = ARRAY_MAX_CAP;
    aList = new objPos[ARRAY_MAX_CAP];

    cout << "Default constructor called" << endl;
}

objPosArrayList::objPosArrayList(const objPosArrayList &sList) // Copy constructor
{
    listSize = sList.listSize;
    arrayCapacity = sList.arrayCapacity;
    aList = new objPos[ARRAY_MAX_CAP];

    for(int i = 0; i < listSize; i++)
    {
        aList[i] = sList.aList[i];
    }

    cout << "copy constructor called" << endl;
}

objPosArrayList::~objPosArrayList() // Destructor
{
    delete[] aList;

    cout << "destructor called" << endl;
}

int objPosArrayList::getSize() const
{
    return listSize;
}

void objPosArrayList::insertHead(objPos thisPos)
{
    if(listSize == arrayCapacity)
    {
        cout << "Array is full" << endl;
        resizeArray();
    }

    for(int i = listSize; i > 0; i--)
    {
        aList[i] = aList[i - 1];
    }

    aList[0] = thisPos;
    listSize++;
}

void objPosArrayList::insertTail(objPos thisPos)
{
    if(listSize == arrayCapacity)
    {
        cout << "Array is full" << endl;
        resizeArray();
    }

    aList[listSize] = thisPos;
    listSize++;
}

void objPosArrayList::removeHead()
{
    if(listSize == 0)
    {
        cout << "list is empty" << endl;
        return;
    }

    for(int i = 0; i < listSize - 1; i++)
    {
        aList[i] = aList[i + 1];
    }

    listSize--;
}

void objPosArrayList::removeTail()
{
    if(listSize == 0)
    {
        cout << "list is empty" << endl;
        return;
    }

    listSize--;
}

objPos objPosArrayList::getHeadElement() const
{
    return aList[0];
}

objPos objPosArrayList::getTailElement() const
{
    return aList[listSize - 1];
}

objPos objPosArrayList::getElement(int index) const
{
    return aList[index];
}

void objPosArrayList::resizeArray()
{
    int newCapacity = arrayCapacity * 2;

    objPos* newArray = new objPos[newCapacity];

    for(int i = 0; i < listSize; i++)
    {
        newArray[i] = aList[i];
    }

    delete[] aList;

    aList = newArray;
    arrayCapacity = newCapacity;
}