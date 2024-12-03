#include "objPosArrayList.h"
#include "MacUILib.h"

// Paste your Tested implementation here.
// Paste your Tested implementation here.
// Paste your Tested implementation here.

objPosArrayList::objPosArrayList() // Default constructor
{
    listSize = 0;
    arrayCapacity = ARRAY_MAX_CAP;
    aList = new objPos[ARRAY_MAX_CAP];
}

objPosArrayList::objPosArrayList(const objPosArrayList &sList) // Copy constructor
{
    listSize = sList.listSize;
    arrayCapacity = sList.arrayCapacity;
    aList = new objPos[ARRAY_MAX_CAP];

    for (int i = 0; i < listSize; i++)
    {
        aList[i] = sList.aList[i];
    }
}

objPosArrayList &objPosArrayList::operator=(const objPosArrayList &array)
{
    if (this != &array)
    {
        this->listSize = array.getSize();
        for (int i = 0; i < this->listSize; i++)
        {
            this->aList[i] = array.aList[i];
        }
    }
    return *this;
}

objPosArrayList::~objPosArrayList() // Destructor
{
    delete[] aList;
}

int objPosArrayList::getSize() const
{
    return listSize;
}

void objPosArrayList::insertHead(objPos thisPos)
{
    if (listSize == arrayCapacity)
    {
        MacUILib_printf("Array is full");
        resizeArray();
    }

    for (int i = listSize; i > 0; i--)
    {
        aList[i] = aList[i - 1];
    }

    aList[0] = thisPos;
    listSize++;
}

void objPosArrayList::insertTail(objPos thisPos)
{
    if (listSize == arrayCapacity)
    {
        MacUILib_printf("Array is full");
        resizeArray();
    }

    aList[listSize] = thisPos;
    listSize++;
}

void objPosArrayList::removeHead()
{
    if (listSize == 0)
    {
        MacUILib_printf("List is empty");
        return;
    }

    for (int i = 0; i < listSize - 1; i++)
    {
        aList[i] = aList[i + 1];
    }

    listSize--;
}

void objPosArrayList::removeTail()
{
    if (listSize == 0)
    {
        MacUILib_printf("List is empty");
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
    if (index < 0 || index >= listSize)
    {
        MacUILib_printf("Invalid index");
        return objPos();
    }

    return aList[index];
}

void objPosArrayList::resizeArray()
{
    int newCapacity = arrayCapacity * 2;

    objPos *newArray = new objPos[newCapacity];

    for (int i = 0; i < listSize; i++)
    {
        newArray[i] = aList[i];
    }

    delete[] aList;

    aList = newArray;
    arrayCapacity = newCapacity;
}