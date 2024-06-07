#ifndef INHABITANT_H
#define INHABITANT_H

#include "settings.h"
#include "neighborhood.h"

class InhabitantIntent{
public:
    const InhabitantAction action;
    const Position where;

    InhabitantIntent
        (InhabitantAction _action = NIC, Position _where = NOWHERE)
        :action(_action), where(_where){}
};

class Neighborhood;

class Inhabitant
{
protected:
    char symbol;

public:

    Inhabitant(char _symbol = SimulationSettings::getSettings().charNieokreslony);
    Inhabitant(const Inhabitant &inhabitant);
    virtual char whichSymbol() const final;
    virtual ~Inhabitant();
    virtual InhabitantType whoAreYou() = 0;
    virtual InhabitantIntent takeAction(Neighborhood neighborhood) = 0;
    virtual Inhabitant *getPotomek() = 0;
    virtual void getPrey(Inhabitant * inhabitant) = 0;
};

#endif // INHABITANT_H
