#ifndef OBJPOS_ARRAYLIST_H
#define OBJPOS_ARRAYLIST_H

#define ARRAY_MAX_CAP 200

#include "objPos.h"

class objPosArrayList
{
    private:
        // pointer to the start of the objPos array
        objPos* aList;
        // Number of valid elements in the list
        int listSize;
        // The number of elements allocated on the heap array
        int arrayCapacity;

    public:

        // constructors/ destructors 
        objPosArrayList();
        ~objPosArrayList();

        // Methods
        int getSize() const;
        void insertHead(objPos thisPos);
        void insertTail(objPos thisPos);
        void removeHead();
        void removeTail();
        
        // Adding more methods with objPos return type
        objPos getHeadElement() const;
        objPos getTailElement() const;
        objPos getElement(int index) const;
};

#endif