#include "inhabitant.h"

Inhabitant::Inhabitant(char _symbol) {
    symbol = _symbol;
}

Inhabitant::Inhabitant(const Inhabitant &inhabitant){
    symbol = inhabitant.symbol;
}

char Inhabitant::whichSymbol() const
{
    return symbol;
}

Inhabitant::~Inhabitant()
{

}
