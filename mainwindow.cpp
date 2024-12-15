#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->resize(800, 800);

    this->table1 = new displayHall(&(this->first));
    this->table2 = new displayHall(&(this->second));

    this->tables.addWidget(this->table1);
    this->tables.addWidget(this->table2);

    this->controller1 = new eventControl(&(this->first), (this->table1));
    this->controller2 = new eventControl(&(this->second), (this->table2));


    this->controllers.addWidget(this->controller1);
    this->controllers.addWidget(this->controller2);

    this->Layout.addLayout(&(this->tables));
    this->Layout.addLayout(&(this->controllers));

    this->start.setText("Launch");
    this->Layout.addWidget(&(this->start));

    QWidget *widget = new QWidget(this);
    widget->setLayout(&(this->Layout));
    setCentralWidget(widget);

    QObject::connect(&(this->first), SIGNAL(floorChanged(int, int)), this->table1, SLOT(redraw(int, int)));
    QObject::connect(&(this->second), SIGNAL(floorChanged(int, int)), this->table2, SLOT(redraw(int, int)));

    QObject::connect(&(this->first), SIGNAL(passangerTaken(int)), this->table1, SLOT(take(int)));
    QObject::connect(&(this->second), SIGNAL(passangerTaken(int)), this->table2, SLOT(take(int)));

    QObject::connect(&(this->first), SIGNAL(passangerReleased(int, int)), this->table1, SLOT(release(int, int)));
    QObject::connect(&(this->second), SIGNAL(passangerReleased(int, int)), this->table2, SLOT(release(int, int)));

    QObject::connect(&(this->start), SIGNAL(clicked()), this, SLOT(elevators()));

    QObject::connect(&(this->first), SIGNAL(finished()), this, SLOT(stop()));
    QObject::connect(&(this->second), SIGNAL(finished()), this, SLOT(stop2()));
}

void MainWindow::elevators(){
    this->first.moveToThread(&(this->thread1));
    this->second.moveToThread(&(this->thread2));

    QObject::connect(&(this->thread1), SIGNAL(started()), &(this->first), SLOT(loop()));
    QObject::connect(&(this->thread2), SIGNAL(started()), &(this->second), SLOT(loop()));

    this->thread1.start();
    this->thread2.start();
}

void MainWindow::stop(){
    this->thread1.quit();
}

void MainWindow::stop2(){
    this->thread2.quit();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete this->table1;
    delete this->table2;
    delete this->controller1;
    delete this->controller2;
}

