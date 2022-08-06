#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setEvents();

    Rotor rotor;
    initAll();
}


MainWindow::~MainWindow()
{
    allOff();
    delete ui;
}

void MainWindow::initAll(){
    rotor.rotate(DIRECTION_CW,ROTATE_OFF);
    rotor.rotate(DIRECTION_CCW,ROTATE_OFF);
}

void MainWindow::allOff(){
    rotor.rotate(DIRECTION_CW,ROTATE_OFF);
    rotor.rotate(DIRECTION_CCW,ROTATE_OFF);
}


void MainWindow::setEvents()
{
    connect(ui->btnCw, &QPushButton::pressed, this, &MainWindow::cwPress);
    connect(ui->btnCw, &QPushButton::released, this, &MainWindow::cwRelease);
    connect(ui->btnCcw, &QPushButton::pressed, this, &MainWindow::ccwPress);
    connect(ui->btnCcw, &QPushButton::released, this, &MainWindow::ccwRelease);
}



void MainWindow::cwPress()
{
    qInfo()<< "cwPress";
    rotor.rotate(DIRECTION_CW,ROTATE_ON);
    rotor.rotate(DIRECTION_CCW,ROTATE_OFF);
}
void MainWindow::cwRelease()
{
    qInfo()<< "cwRelease";
    rotor.rotate(DIRECTION_CW,ROTATE_OFF);
    rotor.rotate(DIRECTION_CCW,ROTATE_OFF);
}

void MainWindow::ccwPress()
{
    qInfo()<< "ccwPress";
    rotor.rotate(DIRECTION_CCW,ROTATE_ON);
    rotor.rotate(DIRECTION_CW,ROTATE_OFF);
}
void MainWindow::ccwRelease()
{
    qInfo()<< "ccwRelease";
    rotor.rotate(DIRECTION_CCW,ROTATE_OFF);
    rotor.rotate(DIRECTION_CW,ROTATE_OFF);
}
