#ifndef DISPLAYHALL_H
#define DISPLAYHALL_H

#include <QTableWidget>
#include <QHeaderView>
#include "elevator.h"

class displayHall : public QWidget
{
    Q_OBJECT

    Elevator *first;
    QHBoxLayout layout;
public:
    QTableWidget display1;
    displayHall(Elevator *uno);

public slots:
    void redraw(int floor, int dir);
    void release(int floor, int dir);
    void take(int floor);
};

#endif // DISPLAYHALL_H
