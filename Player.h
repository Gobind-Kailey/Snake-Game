#ifndef PLAYER_H
#define PLAYER_H

#include "GameMechs.h"
#include "objPos.h"
#include "objPosArrayList.h"
#include "Food.h"

class Player
{
    // Construct the remaining declaration from the project manual.

    // Only some sample members are included here

    // You will include more data members and member functions to complete your design.

    
    public:
        // This is the direction state
        enum Dir {DOWN, UP, LEFT, RIGHT, STOP};
        // This is the speed state  
        enum levels {L0, L1, L2, L3, L4}; 

        

        Player(GameMechs* thisGMRef, Food* thisFREf, Player* thisPRef); // Constructor 
        ~Player(); // Destructor 

        objPosArrayList* getPlayerPos() const; // Upgrade this in iteration 3.       
        int updatePlayerSpeed(); 
        void updatePlayerDir();
        void movePlayer();

        // Didnt end up using below methods
        // bool checkSelfCollision(); 
        // void increasePlayerLength();

        // This will help with setting the speed of the game. 
        int delay;

        // More methods to be added here    

    private:
        objPos playerPos; 
        objPosArrayList *playerPosList;// Upgrade this in iteration 3.   
        // for the direction state   
        enum Dir myFSMMode;
        // for the speed level 
        enum levels level; 

        // Need a reference to the Main Game Mechanisms
        GameMechs* mainGameMechsRef;
        Food* mainFoodRef;
        Player* mainPlayerRef;
};

#endif