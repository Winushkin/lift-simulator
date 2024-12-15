#ifndef FLOOR_H
#define FLOOR_H


class Floor
{
    int number;
    int countUp = 0;
    int countDown = 0;

public:
    Floor();
    Floor(int i);
    void setCountUp(int c);
    void setCountDown(int c);
    int getCountUp();
    int getCountDown();
};

#endif // FLOOR_H
