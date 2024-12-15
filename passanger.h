#ifndef PASSANGER_H
#define PASSANGER_H

#include <random>

enum direction{
    LAST,
    FIRST
};

class Passanger
{
    int currentFloor;
    int destinationFloor;
    int randFloor();

public:
    direction where;
    Passanger();
    Passanger(int c, direction w);
    int getDestFloor();
};

#endif // PASSANGER_H
