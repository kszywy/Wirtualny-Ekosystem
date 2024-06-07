#ifndef ORGANISM_H
#define ORGANISM_H


class Organism
{
public:
    const unsigned short mealLimit;
    const unsigned short costPotomek;
private:
    unsigned short lifeCounter;
    unsigned short mealCounter ;

public:
    Organism(unsigned short lifeSpan,
             unsigned short mealLimit,
             unsigned short costPotomek);

    bool isAlive() const
    {
        return lifeCounter > 0;
    }

    bool isHungry() const
    {
        return isAlive() && mealCounter < mealLimit;
    }

    bool isDescending() const
    {
        return isAlive() && mealCounter > costPotomek;
    }

    unsigned short showLifeCounter() const
    {
        return lifeCounter;
    }

    unsigned short showMealCounter() const
    {
        return mealCounter;
    }

    bool meal();
    bool descendant();

    void simulationStep();

};

#endif // ORGANISM_H

