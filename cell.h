#ifndef CELL_H
#define CELL_H

#include "neighborhood.h"
#include "inhabitant.h"
#include "environment.h"

class Cell
{
private:
    Inhabitant * occupant;

public:
    Cell();
    Cell(Cell &otherCell);
    ~Cell();

    Cell &operator = (Cell &otherCell);

    void acquireOccupant(Inhabitant * homelessOccupant);

    Inhabitant * loseOccupant();

    bool filled() const {return occupant != nullptr;}

    InhabitantType whoLivesHere(){
        return filled() ? occupant -> whoAreYou() : PUSTKA;
    }

    bool isOccupantAlive() const;

    char whichSymbol() const;

    InhabitantIntent activateOccupant(Neighborhood neighborhood){
        return occupant -> takeAction(neighborhood);
    }

private:

    friend void Environment::takeAction(unsigned int row, unsigned int column);

    Inhabitant *letGoOfPotomek(){
        return occupant -> getPotomek();
    }

    void getPrey(Inhabitant *prey){
        occupant -> getPrey(prey);
    }

};

#endif // CELL_H
