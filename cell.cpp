#include "cell.h"

Cell::Cell():occupant(nullptr) {}

Cell::Cell(Cell &otherCell){
    if (otherCell.filled()){
        occupant = otherCell.occupant;
        otherCell.occupant = nullptr;
    }else
        occupant = nullptr;
}

Cell::~Cell(){
    if (occupant != nullptr)
        delete occupant;
}

Cell &Cell::operator = (Cell &otherCell){
    Inhabitant * tmp  = occupant;
    occupant = otherCell.occupant;
    otherCell.occupant = tmp;
    return *this;
}

void Cell::acquireOccupant(Inhabitant *homelessOccupant)
{
    if (!filled()){
        occupant = homelessOccupant;
        homelessOccupant = nullptr;
    }
}

Inhabitant *Cell::loseOccupant()
{
    Inhabitant * tmp = nullptr;

    if (filled()){
        tmp = occupant;
        occupant = nullptr;
    }

    return tmp;
}

bool Cell::isOccupantAlive() const
{
    if (filled()){
        InhabitantType r = occupant -> whoAreYou();
        return r == GLON || r == GRZYB || r == BAKTERIA;
    }else
        return false;
}

char Cell::whichSymbol() const
{
    if (!filled()) return SimulationSettings::
            getSettings().charEmptyCell;
    else return occupant->whichSymbol();
}
