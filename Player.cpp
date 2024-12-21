#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "objPosArrayList.h"
#include "GameMechs.h"
#include "Player.h"
#include "Food.h"

 


// This would be your constructor. 
Player::Player(GameMechs* thisGMRef, Food* thisFREf, Player* thisPRef)
{
    mainGameMechsRef = thisGMRef;
    myFSMMode = STOP; // default state to stop 
    mainFoodRef= thisFREf; 
    mainPlayerRef = thisPRef;

     
    
    
    // Creating objPosArrayList for snake body coordinates 

    // Having the program start at a rest position. 
    level = L0;
    delay = 0; 

    // more actions to be included
    // We divide by 2, so that we could start in the middle. 
    playerPos.pos ->x = mainGameMechsRef ->getBoardSizeX() /2;
    playerPos.pos ->y = mainGameMechsRef ->getBoardSizeY() /2;
    playerPos.symbol = '*';
    objPos tempPos;
    tempPos.setObjPos(playerPos.pos ->x,playerPos.pos ->y,playerPos.symbol);
    


    // holds all of the elements on the heap. 
    playerPosList = new objPosArrayList();
    playerPosList->insertHead(tempPos);

    

}


Player::~Player()
{
    // delete any heap members here
    // nothing is placed in the heap for now
    // so you could leave empty for now. 
    delete playerPosList;
}

objPosArrayList* Player::getPlayerPos() const
{
    return playerPosList;
     // this is return by value. 
}




// this function sets the speed of the snake
int Player::updatePlayerSpeed()
{

    char input = mainGameMechsRef->getInput();
    // using = to increase speed
    // using - to decrease speed 
    switch (level)
    {
        case L0:
            if (input == '='){
                level = L1;
                break;
            }
            delay = 125000;  // 125000 --> 0.125
            break;
        case L1:
        // Whenever we press = it increases the speed, otherwise it will decrease the speed. 
            if (input == '='){ 
                level = L2;
                break;
            }
            else if (input == '-'){
                level = L0;
                break;
            }
            delay = 105000;  // 105000 --> 0.105 // reducing the delay, hence making it faster. 
            break;
        case L2:
            if (input == '='){
                level = L3;
                break;
            }
            else if (input == '-'){
                level = L1;
                break;
            }
            delay = 85000;  // 85000 --> 0.085
            break;
        
        case L3:
            if (input == '='){
                level = L4;
                break;
            }
            else if (input == '-'){
                level = L2;
                break;
            }
            delay = 65000;  // 65000 --> 0.065
            break;
        case L4:
            if (input == '-'){
                level = L3;
                break;
            }
            delay = 45000;  // 45000 --> 0.045
            break;
        default:
            delay = L0;
            break;
    }
    return delay; // the delay will set the speed of the snake

}

void Player::updatePlayerDir()
{
    // PPA3 input processing logic  
    // This switch case is used to determine which movement state it is in. 
    char input = mainGameMechsRef->getInput();
    // int stopped = 1; // start the game off stopped, this helps us in the printing stage. 
    
    // Should this be placed in here? 
    if(input != 0)  // if not null character
    {
        switch(input)
        {                      
            case '\033':  // exit
                mainGameMechsRef->setExitTrue();
                break;
                
            default:
                break;
       
        case 'w':
            if (myFSMMode != DOWN){
                    myFSMMode = UP;
                break;
            } else {
                break;
            }
    
        case 'a':
            if (myFSMMode != RIGHT){
                    myFSMMode = LEFT;
                break;
            } else {
                break;
            }

        case 's':
            if (myFSMMode != UP){
                    myFSMMode = DOWN;
                break;
            } else {
                break;
            }
        

        case 'd':
            if (myFSMMode != LEFT){
                    myFSMMode = RIGHT;
                break;
            } else {
                break;
            }
        input = 0;
    }
    }
    // Clearing the output 
    mainGameMechsRef->clearInput();

}



void Player::movePlayer()
{
    
    // PPA3 Finite State Machine logic

    // Current head 
    objPos currentHead= playerPosList->getHeadElement();
    
    

    switch (myFSMMode)
    {
    case LEFT:
        currentHead.pos ->x --; // Shifting snake left by 1 character
        if (currentHead.pos ->x < 1){
            currentHead.pos ->x = mainGameMechsRef->getBoardSizeX() - 2;
        }
        break;

    
    case RIGHT:
        currentHead.pos ->x ++; // Shifting snake right by 1 character
        if (currentHead.pos ->x > mainGameMechsRef->getBoardSizeX() - 2){
            currentHead.pos ->x = 1;
        }
        break;

        
    case UP: 
        currentHead.pos ->y --; // Shifting snake up by 1 character
        if (currentHead.pos ->y < 1){
            currentHead.pos ->y = mainGameMechsRef->getBoardSizeY() -2;
        }
        break;

        

    case DOWN: 
        currentHead.pos ->y ++; // Shifting snake down by 1 character
        if (currentHead.pos ->y > mainGameMechsRef->getBoardSizeY() -2){
            currentHead.pos ->y = 1;
        }
        break;

    
    default:
        break;
    }

    
    objPos tempFood;
    // getting access to foodbucket 
    objPosArrayList* foodBucket = mainFoodRef->getFoodBucket();
    

    //Check for self-collision
    for (int i = 1; i < playerPosList->getSize(); i++) // Start from index 1 to skip the head
    {

        objPos bodyPart = playerPosList->getElement(i);
        if (currentHead.isPosEqual(&bodyPart))
        {
            mainGameMechsRef->setLoseFlag(); // Set the lose flag
            mainGameMechsRef->setExitTrue(); // Exit the game
            return; // End the movePlayer method early

        }
    }


    // new current head should be inserted to the head of the list
    playerPosList->insertHead(currentHead);
    //then, remove tail
    playerPosList->removeTail();
    
    

    // starting off with no collsion. 
    bool collsion = false; 
    // looping through the size of the bucket 
    for (int i = 0; i < foodBucket->getSize(); i++)
    {
        tempFood = foodBucket->getElement(i);
        // if (currentHead.pos->x == tempfoodpos.pos->x && currentHead.pos->y == tempfoodpos.pos->y)
        if(currentHead.isPosEqual(&tempFood))
        {
            // If it is a non-special food, we increament score by 1 and increase size of snake 
            if (tempFood.symbol == 'o') {
                mainGameMechsRef->incrementScore();
                playerPosList->insertHead(currentHead);
            } 
            else if (tempFood.symbol == '!') {
                for(int s = 0; s < 10; s++)
                    {
                        mainGameMechsRef->incrementScore();
                    } // No length increase
            } 
            // Incrementing the score when '@' is ate, and increasing snake size by 5
            else if (tempFood.symbol == '@') {
                for(int s = 0; s < 5; s++)
                    {
                        mainGameMechsRef->incrementScore();
                    }

                    for(int s = 0; s < 5; s++)
                    {
                        playerPosList->insertHead(currentHead);
                    }
            }


            for(int g = 0; g < 5; g++) // empties food bucket so old food doesn't remain 
            {
                foodBucket->removeTail();
            }

            // generating more food after emptying food bucket. 
            mainFoodRef ->generateFood(playerPosList);
            //playerPosList->insertHead(currentHead); 
            
            collsion = true; 
            break; 
        }
        

    }
            
}   

