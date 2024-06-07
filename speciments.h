#ifndef SPECIMENTS_H
#define SPECIMENTS_H

#include "organism.h"
#include "inhabitant.h"

class Glon: protected Organism, public Inhabitant{
public:
    Glon();
    virtual InhabitantType whoAreYou() final;

    virtual InhabitantIntent takeAction(Neighborhood neighborhood);
    virtual Inhabitant * getPotomek();
    virtual void getPrey(Inhabitant * inhabitant);

};

class Grzyb: protected Organism, public Inhabitant{
public:
    Grzyb();
    virtual InhabitantType whoAreYou() final;

    virtual InhabitantIntent takeAction(Neighborhood neighborhood);
    virtual Inhabitant * getPotomek();
    virtual void getPrey(Inhabitant * inhabitant);

};

class Bakteria: protected Organism, public Inhabitant{
public:
    Bakteria();
    virtual InhabitantType whoAreYou() final;

    virtual InhabitantIntent takeAction(Neighborhood neighborhood);
    virtual Inhabitant * getPotomek();
    virtual void getPrey(Inhabitant * inhabitant);

};



#endif // SPECIMENTS_H
