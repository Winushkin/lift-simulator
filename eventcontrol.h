#ifndef EVENTCONTROL_H
#define EVENTCONTROL_H

#include <algorithm>
#include "displayhall.h"

class eventControl : public QWidget
{
    Q_OBJECT
    Elevator *elevator;
    displayHall *hall;

    QSpinBox upSpinBox;
    QSpinBox downSpinBox;
    QSpinBox floorSpinBox;
    QLabel floorLab, upLab, downLab;
    QGridLayout layout;
    QPushButton confirmButton;
public:
    eventControl(Elevator *elevator, displayHall *hall);


public slots:
    void generatePassangers();
    void extremeFloors(int i);

};

#endif // EVENTCONTROL_H
