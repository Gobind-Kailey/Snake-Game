#include "objPosArrayList.h"

// Check lecture contents on general purpose array list construction, 
// and modify it to support objPos array list construction.

// constructor 
objPosArrayList::objPosArrayList()
{
    // 200 elements on the heap
    aList = new objPos[ARRAY_MAX_CAP]; 
    //no valid element in the list at the beginning
    listSize = 0;
    //array capacity is set to max 
    arrayCapacity = ARRAY_MAX_CAP; 
}

// destructor. 
objPosArrayList::~objPosArrayList()
{
    //deallocating the array from the heap
    delete[] aList; 
}

int objPosArrayList::getSize() const
{
    // returns the size of the list 
    return listSize;
}

void objPosArrayList::insertHead(objPos thisPos)
{
// inserting at the head of the the list 
//shifting elements, it is needed in order to add a header to the list and index 0 should be empty
    if(listSize<arrayCapacity){ 
        for(int i = listSize; i>0; i--){
            // Starting from the right-side and shifting one to the right
            aList[i].setObjPos(aList[i-1]); 
        }

        // Now there is space to add a value to the first index/head. 
        aList[0].setObjPos(thisPos);

        listSize++;
    }
}

void objPosArrayList::insertTail(objPos thisPos)
{
    // element shifting is not needed as we are adding at the end
    if(listSize < arrayCapacity){ 
        aList[listSize].setObjPos(thisPos);
        listSize++;
    }
}

void objPosArrayList::removeHead()
{
    if(listSize < arrayCapacity){ 
        // removing the head by shifting the element to the left
        for(int i =0; i< listSize; i++){ 
            aList[i].setObjPos(aList[i+1]);
        }

        listSize--; // updating the listSize as the head is removed
    }
}

// Removing the tail
void objPosArrayList::removeTail()
{
    if(listSize< arrayCapacity){
        listSize--; //removing the tail, shifting is not needed
    }
}

// getting head element 
objPos objPosArrayList::getHeadElement() const
{
    if(listSize>0){
        return aList[0];
    }
         
}

// getting tail element 
objPos objPosArrayList::getTailElement() const
{
    if(listSize>0){
        return aList[listSize-1];
    }
}

// getting an element at a specified index. 
objPos objPosArrayList::getElement(int index) const
{
    // making sure that it is a valid index and then returning 
    if(index>=0 && index<listSize){
        return aList[index];
    }
}