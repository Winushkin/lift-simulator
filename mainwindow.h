#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "eventcontrol.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    displayHall *table1, *table2;
    eventControl *controller1, *controller2;

    QThread thread1, thread2;

    QPushButton start;
    QVBoxLayout Layout;
    QHBoxLayout tables, controllers;

    Elevator first;
    Elevator second;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void stop();
    void stop2();
    void elevators();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
