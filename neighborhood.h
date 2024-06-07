#ifndef NEIGHBORHOOD_H
#define NEIGHBORHOOD_H

#include "settings.h"

class Neighborhood
{

private:
    InhabitantType neighbor[3][3];

    InhabitantType * elementInside(Position position);

    static Position drawPosition();

public:
    Neighborhood
        (InhabitantType type = NIEZNANE);

    void specifyNeighbor
        (Position position, InhabitantType type);

    InhabitantType whoIsNeighbor
        (Position position);

    unsigned short howMany
        (InhabitantType type) const;

    Position drawNeighbor
        (InhabitantType type);

    static void changeIndexesByPosition
        (Position position, long &row, long &col);

    static void changeIndexesByPosition
        (Position position, unsigned int &row, unsigned int &col);

};

#endif // NEIGHBORHOOD_H
