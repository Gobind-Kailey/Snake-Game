#ifndef OBJPOS_H
#define OBJPOS_H   

// Not really a C++ thing
typedef struct 
{
    int x;
    int y;
} Pos;

class objPos
{
    public:
        Pos* pos;        
        char symbol;

        objPos(); // default constructor (1/4)
        objPos(int xPos, int yPos, char sym); //Other/Specialized Constructor
        
        // Respect the rule of six / minimum four
        // [TODO] Implement the missing special member functions to meet the minimum four rule
        
        objPos(const objPos &copy_obj);            // copy constructor (2/4) 
        objPos& operator=(const objPos &copy_obj); // copy assignment operator (3/4)
        ~objPos(); // (4/4) destructor

        // Declaring setters 
        void setObjPos(objPos o);        
        void setObjPos(int xPos, int yPos, char sym);  

        // Declaring getters 
        objPos getObjPos() const;
        char getSymbol() const;
        char getSymbolIfPosEqual(const objPos* refPos) const;
        
        // Checks if the postion is equal 
        bool isPosEqual(const objPos* refPos) const;
};

#endif