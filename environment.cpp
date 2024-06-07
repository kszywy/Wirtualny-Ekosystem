#include <iostream>
#include <fstream>
#include <sstream>
#include "cell.h"
#include "randomgenerator.h"
#include "speciments.h"
#include "settings.h"
#include "environment.h"

Environment::Environment(unsigned int _rows,
                         unsigned int _columns)
    :rows(_rows),
    columns(_columns),
    numberOfCells(_rows * _columns)
{
    cell = new Cell*[rows];
    for (unsigned int i = 0; i < rows; i++)
        cell[i] = new Cell[columns];
}

Environment::~Environment()
{
    for (unsigned int i = 0; i < rows; i++)
        delete [] cell[i];
    delete [] cell;

}

void Environment::occupy(Inhabitant *inhabitant, unsigned int row, unsigned int column)
{
    if (row < rows && column < columns)
        cell[row][column].acquireOccupant(inhabitant);
}

Neighborhood Environment::specifyNeighborhood(unsigned int row, unsigned int column) const
{
    Neighborhood neighborhood(SCIANA);

    long row1, column1;

    for (Position p: {P, PG, G, LG, L, LD, D, PD}){
        row1 = row;
        column1 = column;

        Neighborhood::changeIndexesByPosition(p, row1, column1);

        if (row1 >= 0 &&
            row1 < rows &&
            column1 >= 0 &&
            column1 < columns)
        {
            neighborhood.specifyNeighbor(p, cell[row1][column1].whoLivesHere());
        }
    }
    return neighborhood;
}

unsigned long Environment::numberOf(InhabitantType type) const
{
    unsigned long counter = 0;

    for (unsigned int w = 0; w < rows; w++)
        for (unsigned int k = 0; k < columns; k++)
            if (cell[w][k].whoLivesHere() == type)
                counter++;

    return counter;
}

bool Environment::isDead()
{
    return numberOf(GLON) + numberOf(GRZYB) + numberOf(BAKTERIA) == 0;
}

void Environment::takeAJump(unsigned int row, unsigned int column)
{
    if (!cell[row][column].isOccupantAlive() ||
        cell[row][column].whoLivesHere() == GLON)
        return;

    Neighborhood neighborhood = specifyNeighborhood(row, column);

    if (neighborhood.howMany(PUSTKA) > 0){
        Position position = neighborhood.drawNeighbor(PUSTKA);

        unsigned int row1 = row, column1 = column;

        Neighborhood::changeIndexesByPosition(position, row1, column1);

        cell[row1][column1] = cell[row][column];
    }
}

void Environment::takeAction(unsigned int row, unsigned int column)
{
    if (!cell[row][column].isOccupantAlive())
        return;

    Neighborhood neighborhood = specifyNeighborhood(row, column);

    InhabitantIntent intent = cell[row][column].activateOccupant(neighborhood);

    unsigned int row1 = row, column1 = column;

    Neighborhood::changeIndexesByPosition(intent.where, row1, column1);

    Inhabitant *m = nullptr;

    switch (intent.action){
    case NIC:
        takeAJump(row, column);
        break;

    case POTOMEK:
        m = cell[row][column].letGoOfPotomek();
        cell[row1][column1].acquireOccupant(m);
        break;

    case POLOWANIE:
    case ROZKLAD:
        m = cell[row1][column1].loseOccupant();
        cell[row][column].getPrey(m);
        break;
    }

}

void Environment::takeSimulationStep()
{
    VectorOfIndexes2D randomIndexes = RandomGenerator::randomIndexes(rows, columns);

    for(Index2D index : randomIndexes)
        takeAction(index.row, index.column);
}

std::string Environment::toText() const
{
    std::string text = "";
    char sep = SimulationSettings::getSettings().charSeparator;

    for (unsigned int w = 0; w < rows; w++){
        for (unsigned int k = 0; k < columns; k++){
            if (k>0) text += sep;
            text += cell[w][k].whichSymbol();
        }
        text += '\n';
    }

    text += "\nGlony * : "
            + std::to_string(numberOf(GLON))
            + "\nGrzyby # : "
            + std::to_string(numberOf(GRZYB))
            + "\nBakterie @ : "
            + std::to_string(numberOf(BAKTERIA))
            + "\nMartwe + : "
            + std::to_string(numberOf(TRUP))
            + '\n';
    return text;
}

std::ostream &operator<<(std::ostream &stream,
                         const Environment &environment)
{
    stream << environment.toText();
    return stream;
}

Environment Environment::readFromFile(std::string fileName)
{
    std::ifstream file(fileName);
    std::stringstream text("");
    if (file){
        text << file.rdbuf();
        file.close();
    }

    std::string save = text.str();

    unsigned int rows = 0, columns = 0;
    bool firstLine = true;
    for (char c : save){
        if (c != '\n'){
            if (firstLine && c != ' ') columns++;
        } else {
            firstLine = false;
            if (c == '\n') rows++;
        }
    }

    Environment environment(rows, columns);

    char glon = SimulationSettings::getSettings().charGlon;
    char grzyb = SimulationSettings::getSettings().charGrzyb;
    char bakteria = SimulationSettings::getSettings().charBakteria;
    char pusta = SimulationSettings::getSettings().charEmptyCell;

    char ch;

    for (unsigned int w = 0; w < rows; w++){
        getline(text, save);
        for (unsigned int k = 0; k < 2*columns; k+=2){
            ch = k<save.size() ? save[k]: pusta;

            if (ch == glon)
                environment.occupy(new Glon(), w, k/2);
            else if (ch == grzyb)
                environment.occupy(new Grzyb(), w, k/2);
            else if (ch == bakteria)
                environment.occupy(new Bakteria(), w, k/2);
        }
    }

    return environment;
}
