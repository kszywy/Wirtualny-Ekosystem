#include "neighborhood.h"
#include "randomgenerator.h"


InhabitantType *Neighborhood::elementInside
    (Position position)
{
    switch (position){
    case P:
        return &neighbor[1][2];
    case PG:
        return &neighbor[0][2];
    case G:
        return &neighbor[0][1];
    case LG:
        return &neighbor[0][0];
    case L:
        return &neighbor[1][0];
    case LD:
        return &neighbor[2][0];
    case D:
        return &neighbor[2][1];
    case PD:
        return &neighbor[2][2];
    case NOWHERE:
        return nullptr;
    }
    return nullptr;
}

Position Neighborhood::drawPosition()
{
    unsigned short min = 0, max = 8;
    return static_cast<Position> (RandomGenerator::drawBetween(min, max));
}

Neighborhood::Neighborhood(InhabitantType type)
{
    for (auto i : {0,1,2})
        for (auto j : {0,1,2})
            neighbor[i][j] = type;

    neighbor[1][1] = NIEZNANE;

}

void Neighborhood::specifyNeighbor(Position position, InhabitantType type)
{
    if (position != NOWHERE){
        *elementInside(position) = type;
    }
}

InhabitantType Neighborhood::whoIsNeighbor(Position position)
{
    if (position != NOWHERE)
        return *elementInside(position);
    else
        return NIEZNANE;
}

unsigned short Neighborhood::howMany(InhabitantType type) const
{
    unsigned short counter = 0;

    for (int i : {0,1,2})
        for(int j : {0,1,2}){
            if (i == 1 && j == 1)
                continue;
            if (neighbor[i][j] == type)
                counter++;
        }
    return counter;
}

Position Neighborhood::drawNeighbor(InhabitantType type)
{
    if (howMany(type) == 0)
        return NOWHERE;
    else{
        Position position = Neighborhood::drawPosition();

        while(whoIsNeighbor(position) != type)
            position = Neighborhood::drawPosition();

        return position;
    }
}

void Neighborhood::changeIndexesByPosition(Position position, long &row, long &col)
{
    if (position == PG || position == P || position == PD)
        col++;
    else if (position == LG || position == L || position == LD)
        col--;
    if (position == LG || position == G || position == PG)
        row--;
    else if (position == LD || position == D || position == PD)
        row++;
}

void Neighborhood::changeIndexesByPosition(Position position, unsigned int &row, unsigned int &col)
{
    long r = static_cast<long> (row);
    long c = static_cast<long> (col);

    changeIndexesByPosition(position, r, c);

    row = static_cast<unsigned int> (r);
    col = static_cast<unsigned int> (c);
}
