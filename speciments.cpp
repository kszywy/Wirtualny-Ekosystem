#include "settings.h"
#include "randomgenerator.h"
#include "speciments.h"

static const SimulationSettings &UST = SimulationSettings::getSettings();

Glon::Glon():
    Organism(RandomGenerator::drawBetween(UST.glonLifeMin, UST.glonLifeMax),
               UST.glonMealLimit, UST.glonPotomekPrice),
               Inhabitant (UST.charGlon){}

InhabitantType Glon::whoAreYou(){
    return isAlive() ? GLON : TRUP;
}

Inhabitant * Glon::getPotomek(){
    Inhabitant * m = nullptr;
    if (descendant()) m = new Glon();
    return m;
}

void Glon::getPrey(Inhabitant * inhabitant){
    if (inhabitant != nullptr) delete inhabitant;
}

InhabitantIntent Glon::takeAction(Neighborhood neighborhood){
    simulationStep();

    if (isAlive() && isDescending() && neighborhood.howMany(PUSTKA) > 0)
        return InhabitantIntent(POTOMEK, neighborhood.drawNeighbor(PUSTKA));

    if (isAlive() && isHungry()) meal();

    if (!isAlive() && symbol != UST.charTrup)
        symbol = UST.charTrup;

    return InhabitantIntent();
}


Grzyb::Grzyb():
    Organism(RandomGenerator::drawBetween(UST.grzybLifeMin, UST.grzybLifeMax),
             UST.grzybMealLimit, UST.grzybPotomekPrice),
    Inhabitant (UST.charGrzyb){}

InhabitantType Grzyb::whoAreYou(){
    return isAlive() ? GRZYB : TRUP;
}

Inhabitant * Grzyb::getPotomek(){
    Inhabitant * m = nullptr;
    if (descendant()) m = new Grzyb();
    return m;
}

void Grzyb::getPrey(Inhabitant * inhabitant){
    if (inhabitant != nullptr){
        if (inhabitant -> whoAreYou() == TRUP) meal();
        delete inhabitant;
    }
}

InhabitantIntent Grzyb::takeAction(Neighborhood neighborhood){
    simulationStep();

    if (isAlive() && isDescending() && neighborhood.howMany(PUSTKA) > 0)
        return InhabitantIntent(POTOMEK, neighborhood.drawNeighbor(PUSTKA));

    if (isAlive() && isHungry() && neighborhood.howMany(TRUP) > 0)
        return InhabitantIntent(ROZKLAD, neighborhood.drawNeighbor(TRUP));

    if (!isAlive() && symbol != UST.charTrup)
        symbol = UST.charTrup;

    return InhabitantIntent();
}


Bakteria::Bakteria():
    Organism(RandomGenerator::drawBetween(UST.bakteriaLifeMin, UST.bakteriaLifeMax),
             UST.bakteriaMealLimit, UST.bakteriaPotomekPrice),
    Inhabitant (UST.charBakteria){}


InhabitantType Bakteria::whoAreYou(){
    return isAlive() ? BAKTERIA : TRUP;
}

Inhabitant * Bakteria::getPotomek(){
    Inhabitant * m = nullptr;
    if (descendant()) m = new Bakteria();
    return m;
}

void Bakteria::getPrey(Inhabitant * inhabitant){
    if (inhabitant != nullptr){
        InhabitantType r = inhabitant -> whoAreYou();
        if (r == GLON || r == GRZYB) meal();
        delete inhabitant;
    }
}

InhabitantIntent Bakteria::takeAction(Neighborhood neighborhood){
    simulationStep();

    if (isAlive() && isDescending() && neighborhood.howMany(PUSTKA) > 0)
        return InhabitantIntent(POTOMEK, neighborhood.drawNeighbor(PUSTKA));

    if (isAlive() && isHungry() && neighborhood.howMany(GLON) > 0)
        return InhabitantIntent(POLOWANIE, neighborhood.drawNeighbor(GLON));

    if (isAlive() && isHungry() && neighborhood.howMany(BAKTERIA) > 0)
        return InhabitantIntent(POLOWANIE, neighborhood.drawNeighbor(BAKTERIA));

    if(!isAlive() && symbol != UST.charTrup)
        symbol = UST.charTrup;

    return InhabitantIntent();
}
