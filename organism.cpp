#include "organism.h"


Organism::Organism(unsigned short lifeSpan,
                   unsigned short mealLimit,
                   unsigned short costPotomek):
    mealLimit(mealLimit),
    costPotomek(costPotomek),
    lifeCounter(lifeSpan),
    mealCounter(0)
{

}


bool Organism::meal()
{
    if(isHungry()){
        mealCounter++;
        return true;
    }
    return false;
}

bool Organism::descendant()
{
    if(isDescending()){
        mealCounter -= costPotomek;
        return true;
    }
    return false;
}

void Organism::simulationStep()
{
    if(isAlive())
        lifeCounter--;
}
