#include "displayhall.h"

displayHall::displayHall(Elevator *uno) : QWidget{}{
    this->first = uno;

    this->display1.setColumnCount(2);
    this->display1.setRowCount(9);

    this->display1.setHorizontalHeaderLabels({"", "People awaiting"});
    this->display1.setVerticalHeaderLabels({"9", "8", "7", "6", "5", "4", "3", "2", "1"});

    QTableWidgetItem *cell1 = new QTableWidgetItem(QString::number(this->first->getCurPas()) + " ↑");
    cell1->setBackground(Qt::green);
    cell1->setTextAlignment(Qt::AlignCenter);
    this->display1.setItem(8, 0, cell1);

    this->display1.resizeColumnsToContents();
    this->display1.horizontalHeader()->setStretchLastSection(true);
    this->display1.verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    this->layout.addWidget(&(this->display1));
    this->setLayout(&(this->layout));
}

void displayHall::redraw(int floor, int dir){

    QString text = QString::number(this->first->getCurPas());

    QTableWidgetItem *cell2 = new QTableWidgetItem("");
    cell2->setBackground(Qt::white);

    if (dir == UP){
        text += " ↑";
        this->display1.setItem(8-floor+1, 0, cell2);
    }
    else if (dir == DOWN){
        text += " ↓";
        this->display1.setItem(8-floor-1, 0, cell2);
    }


    QTableWidgetItem *cell1 = new QTableWidgetItem(text);
    cell1->setBackground(Qt::green);
    cell1->setTextAlignment(Qt::AlignCenter);
    this->display1.setItem(8-floor, 0, cell1);
}

void displayHall::release(int curFloor, int dir){
    QString text = QString::number(this->first->getCurPas());
    if (dir == UP) text += " ↑";
    else if (dir == DOWN) text += " ↓";
    else text += "  ";

    QTableWidgetItem *qTableItem = new QTableWidgetItem(text);
    qTableItem->setBackground(Qt::green);
    qTableItem->setTextAlignment(Qt::AlignCenter);
    this->display1.setItem(8-curFloor, 0, qTableItem);
}

void displayHall::take(int curFloor) {
    QTableWidgetItem *qTableItem = new QTableWidgetItem("UP: " + QString::number(this->first->floors[curFloor].getCountUp()) + " DOWN: " + QString::number(this->first->floors[curFloor].getCountDown()));
    this->display1.setItem(8-curFloor, 1, qTableItem);
}
