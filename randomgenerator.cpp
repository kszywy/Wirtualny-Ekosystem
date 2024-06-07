#include <algorithm>
#include "randomgenerator.h"

std::random_device RandomGenerator::device;

RandomGenerator::RandomGenerator() {}

unsigned short RandomGenerator::drawBetween
    (unsigned short min, unsigned short max)
{
    if (min > max){
        unsigned short tmp = min;
        min = max;
        max = tmp;
    }

    std::uniform_int_distribution<unsigned short> dist(min, max);

    return dist(RandomGenerator::device);
}

long RandomGenerator::drawBetween(long min, long max)
{
    if (min > max){
        long tmp = min;
        min = max;
        max = tmp;
    }

    std::uniform_int_distribution<long> dist(min, max);

    return dist(RandomGenerator::device);
}

int RandomGenerator::drawFromZero(int max)
{
    std::uniform_int_distribution<int> dist(0, max);
    return dist(RandomGenerator::device);
}

VectorOfIndexes2D RandomGenerator::
    randomIndexes(unsigned int rows, unsigned int columns)
{
    VectorOfIndexes2D indexes;
    for (unsigned int w = 0; w < rows; w++)
        for(unsigned int k = 0; k < columns; k++)
            indexes.push_back(Index2D(w, k));

    std::random_shuffle(indexes.begin(), indexes.end(), RandomGenerator::drawFromZero);

    return indexes;
}
