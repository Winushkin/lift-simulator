#ifndef ELEVATOR_H
#define ELEVATOR_H

#include <QDebug>

#include <QObject>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QSpinBox>
#include <QPushButton>
#include <QLabel>
#include <QThread>
#include <QVector>
#include "../../Downloads/0361_Иконников_КР/floor.h"
#include "../../Downloads/0361_Иконников_КР/passanger.h"


#define UP 1
#define IDLE 0
#define DOWN -1


class Elevator : public QObject
{
    Q_OBJECT
    int status = IDLE;
    int currentFloor = 0;
    QVector<Passanger> currentPas;

    void takePassangers();
    void releasePassangers();
    int mDestFloor();
    bool isWaiting();
    int chooseDestFloor();
    QThread thread1;

public:
    QVector<Floor> floors;
    QVector<QVector<Passanger>> queue;

    Elevator();
    int getCurPas();
    int getCurFlr();

public slots:
    void loop();


signals:
    void floorChanged(int floor, int dir);
    void passangerTaken(int floor);
    void passangerReleased(int floor, int dir);
    void finished();
};

#endif // ELEVATOR_H
