#include "objPos.h"

// Constructor 
objPos::objPos()
{
    pos = new Pos;
    pos->x = 0;
    pos->y = 0;
    symbol = 0; //NULL
}

// Special constructor 
objPos::objPos(int xPos, int yPos, char sym)
{
    pos = new Pos;
    pos->x = xPos;
    pos->y = yPos;
    symbol = sym;
}

// Respect the rule of six / minimum four
// [TODO] Implement the missing special member functions to meet the minimum four rule

// Copy constructor (2/4)
objPos::objPos(const objPos &copy_obj)
{
    // preform deep-copy
    pos = new Pos; // Placing it on the heap
    pos ->x = copy_obj.pos -> x;
    pos ->y = copy_obj.pos -> y;
    symbol = copy_obj.symbol;

}

// Copy assignment constructor (3/4)

objPos& objPos::operator=(const objPos &copy_obj) // copy assignment operator
{   
    // this represents the current object
    if(this != &copy_obj)  // Avoid self assignment
    {
        // pos = new Pos; // Placing it on the heap  
        pos ->x = copy_obj.pos -> x;
        pos ->y = copy_obj.pos -> y;
        symbol = copy_obj.symbol;    
    }

    return *this;
}

// Destructor (4/4)

objPos::~objPos()
{
    delete pos; // The [] is used when deleting an array 
    pos = nullptr; // this is to avoid dangling pointer.
}


void objPos::setObjPos(objPos o)
{
    pos->x = o.pos->x;
    pos->y = o.pos->y;
    symbol = o.symbol;
}

void objPos::setObjPos(int xPos, int yPos, char sym)
{
    pos->x = xPos;
    pos->y = yPos;
    symbol = sym;
}

// Used to get the objects position
objPos objPos::getObjPos() const
{
    objPos returnPos;
    returnPos.pos->x = pos->x;
    returnPos.pos->y = pos->y;
    returnPos.symbol = symbol;
    
    return returnPos;
}

// Used to get the object symbol
char objPos::getSymbol() const
{
    return symbol;
}

// Comparing if the x and y values 
bool objPos::isPosEqual(const objPos* refPos) const
{
    return (refPos->pos->x == pos->x && refPos->pos->y == pos->y);
}

char objPos::getSymbolIfPosEqual(const objPos* refPos) const
{
    // if the positions are equal then reutrn the symbol of it aswell. 
    if(isPosEqual(refPos))
        return symbol;
    else
        return 0;
}
