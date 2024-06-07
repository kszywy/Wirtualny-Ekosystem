#ifndef SETTINGS_H
#define SETTINGS_H

// POLSKIW NAZWY DLA ENCJI I AKCJI MIESZKANCOW
enum InhabitantType{GLON, GRZYB, BAKTERIA, PUSTKA, SCIANA, TRUP, NIEZNANE};

enum InhabitantAction{POTOMEK, POLOWANIE, ROZKLAD, NIC};

enum Position{P=0, PG=1, G=2, LG=3, L=4, LD=5, D=6, PD=7, NOWHERE=8};

class SimulationSettings
{
public:

    const char
        charGlon = '*',
        charGrzyb = '#',
        charBakteria = '@',
        charTrup = '+',
        charNieokreslony = '?',
        charEmptyCell = '_',
        charSeparator = ' ';

    unsigned short
        glonLifeMin = 5,
        glonLifeMax = 10,
        glonPotomekPrice = 2,
        glonMealLimit = 6,

        grzybLifeMin = 40,
        grzybLifeMax = 60,
        grzybPotomekPrice = 3,
        grzybMealLimit = 30,

        bakteriaLifeMin = 25,
        bakteriaLifeMax = 40,
        bakteriaPotomekPrice = 3,
        bakteriaMealLimit = 10;

    bool correctCharOfCell(char z) const	{
        return z == charGlon ||
                z == charGrzyb ||
                z == charBakteria ||
                z == charTrup ||
                z == charEmptyCell;
    }

    bool isCorrectSeparator(char z) const {
        return z == charSeparator;
    }


private:
    SimulationSettings(){};
    SimulationSettings
        (SimulationSettings&);

public:
    static SimulationSettings &getSettings(){
        static SimulationSettings settings;
        return settings;
    }

};

#endif // SETTINGS_H
