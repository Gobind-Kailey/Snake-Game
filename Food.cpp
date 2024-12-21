#include "Food.h"
#include "Player.h"
// #include "GameMechs.h"

// This count will be used to determine how many food items will be printed
#define ITEM_COUNT 5

// Constructor 
Food::Food(GameMechs* thisGMRef){
    MechsRef = thisGMRef;
    
    // starting off with not being on the board. 
    foodPos.setObjPos(-1,-1,'o');

    /* Creating the food bucket on the heap, which was orginally a pointer of 
     objPosArrayList type. */
    foodBucket = new objPosArrayList();

    /* Inserting the first element, just so we start off with something 
     even though it's not on the board */
    foodBucket->insertHead(foodPos);
}


Food::~Food(){
    // destructor 
    delete foodBucket;
}

objPosArrayList* Food::getFoodBucket(){
    // returning the foodbucket. 
    return foodBucket;
}

// Setting the food index
void Food::setFoodIndex(int i){
    foodIndex = i;
}

// Getting the food index 
int Food::getFoodIndex(){
    return foodIndex;
}

// This function consists of generating the random coordinates for our food
void Food::generateFood(objPosArrayList* blockOff){

    // This updates every new time. 
    srand(time(NULL));
    
    // Getting access to the boardsize
    int sizeX = MechsRef->getBoardSizeX();
    int sizeY = MechsRef->getBoardSizeY();

    // Looping through for the number of food items we are looking for. 
    for(int b = 0; b < ITEM_COUNT; b++)
    {   
        // used for random character generation 
        char symRandChar;

        // This will keep the game going 
        int repeat = 1;

        // for the first three food, we will just use the 'o' symbol. 
        if(b < 3){
            foodPos.symbol = 'o';
        } 
        else
        {
            
            
        // generating symbol for mystery food. 

            while(repeat == 1)
            {   
                // Special symbols
                char specialSymbols[] = {'!', '@'};
                // randomly choosing one of the random symbols. 
                symRandChar = specialSymbols[rand() % 2];
                
                foodPos.symbol = symRandChar;
                break;
            }
        }
        
        // generating random x and y position. 
        while (repeat == 1)
        {
            // Choosing a random y and x position. 
            int yRand = 1 + rand() % (sizeY - 2); 
            int xRand = 1 + rand() % (sizeX - 2);

            // looping through the size of the snake
            for(int i = 0; i < blockOff->getSize(); i++)
            {
                // tempBody holds current snake element
                objPos tempBody = blockOff->getElement(i);
                
                // Checking if the food equals any of the player positions. 
                if(tempBody.pos->x == xRand && tempBody.pos->y == yRand)
                {
                    // For looping purposes
                    repeat = 1; 
                    break;

                } else {
                    // setting the object position. 
                    foodPos.setObjPos(xRand, yRand, foodPos.symbol);
                    repeat = 0;
                }
            }
        }
        // adding to the end of the tail.
        foodBucket->insertTail(foodPos);
    }


        
}
