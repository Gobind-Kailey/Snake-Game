#ifndef FOOD_H
#define FOOD_H

// gaining access to other files. 
#include <cstdlib>
#include <time.h>
#include "objPos.h"
#include "objPosArrayList.h"
#include "GameMechs.h"

using namespace std;

class Food
{
    private:
        // private data members
        objPos foodPos;
        GameMechs* MechsRef;
        objPosArrayList* foodBucket;
        int foodIndex; // dictates which food to spam depending on index

    public:
        // Construtors/destructors.  
        Food(GameMechs* thisGMRef);
        ~Food();

        // Decaring setters 
        void setFoodIndex(int i);

        // Decaring getters/ other methods 
        int getFoodIndex();

        void generateFood(objPosArrayList* blockOff);

        objPosArrayList* getFoodBucket();
};

#endif