#ifndef RANDOMGENERATOR_H
#define RANDOMGENERATOR_H

#include <random>

class Index2D
{
public:
    unsigned int row, column;
    Index2D(unsigned int _w=0, unsigned int _k=0)
        :row(_w), column(_k){}
};

typedef std::vector<Index2D> VectorOfIndexes2D;


class RandomGenerator
{
private:

    static std::random_device device;
    RandomGenerator();

public:

    static unsigned short drawBetween
        (unsigned short min, unsigned short max);

    static long drawBetween(long min, long max);

    static int drawFromZero(int max);

    static VectorOfIndexes2D randomIndexes
        (unsigned int rows, unsigned int columns);

};

typedef RandomGenerator GEN;

#endif // RANDOMGENERATOR_H
