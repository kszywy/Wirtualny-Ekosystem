#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <string>
#include "settings.h"

class Cell;
class Inhabitant;
class Neighborhood;


class Environment
{
public:
    const unsigned int rows, columns;
    const unsigned long numberOfCells;

    void operator++(int) {takeSimulationStep();}
    bool operator!() {return !isDead();}

private:
    Cell ** cell;

public:
    Environment(unsigned int _rows,
                unsigned int _columns);

    ~Environment();

    void occupy(Inhabitant * inhabitant,
                unsigned int row, unsigned int column);

    Neighborhood specifyNeighborhood(unsigned int row,
                                     unsigned int column) const;

    unsigned long numberOf(InhabitantType type) const;

    bool isDead();

    void takeAJump(unsigned int row, unsigned int column);

    void takeAction(unsigned int row, unsigned int column);

    void takeSimulationStep();

    std::string toText() const;

    static Environment readFromFile(std::string fileName);

};

std::ostream &operator<<(std::ostream &stream,
                            const Environment &environment);

#endif // ENVIRONMENT_H
