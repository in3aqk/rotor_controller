#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "defines.h"
#include <QFloat16>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setEvents();

    Rotor rotor;
    initAll();

    QSettings settings;
}


MainWindow::~MainWindow()
{
    allOff();
    delete ui;
}

void MainWindow::initAll(){

    QCoreApplication::setOrganizationName("Mattiolo Paolo IN3AQK");
    QCoreApplication::setOrganizationDomain("in3aqk.blogspot.com");
    QCoreApplication::setApplicationName("Rotor controller");

    QSettings settings("config.ini", QSettings::IniFormat);

    qInfo() << "Rotation time: " << settings.value("ROTOR/rotation_time").toInt();
    qInfo() << "Last position: " << settings.value("ROTOR/last_position").toInt();

    int isCalibrated = settings.value("ROTOR/is_calibrated").toInt();;
    qInfo()<< "Is calibrated" << isCalibrated;
    if (isCalibrated == 0){
        qInfo() << isCalibrated;
    }

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
    connect(&rotorTimer, SIGNAL(display_heading_sig(qfloat16)), this, SLOT(display_heading_slot(qfloat16)));
}


void MainWindow::cwPress()
{
    qInfo()<< "cwPress";
    rotor.rotate(DIRECTION_CW,ROTATE_ON);
    rotor.rotate(DIRECTION_CCW,ROTATE_OFF);
    rotorTimer.timerGo(DIRECTION_CW);

}
void MainWindow::cwRelease()
{
    qInfo()<< "cwRelease";
    rotor.rotate(DIRECTION_CW,ROTATE_OFF);
    rotor.rotate(DIRECTION_CCW,ROTATE_OFF);
    rotorTimer.timerStop();
}

void MainWindow::ccwPress()
{
    qInfo()<< "ccwPress";
    rotor.rotate(DIRECTION_CCW,ROTATE_ON);
    rotor.rotate(DIRECTION_CW,ROTATE_OFF);
    rotorTimer.timerGo(DIRECTION_CCW);
}
void MainWindow::ccwRelease()
{
    qInfo()<< "ccwRelease";
    rotor.rotate(DIRECTION_CCW,ROTATE_OFF);
    rotor.rotate(DIRECTION_CW,ROTATE_OFF);
    rotorTimer.timerStop();
}

void MainWindow::display_heading_slot(qfloat16 heading){
    qDebug() << "Called";
    ui->lcdAzimut->display(static_cast<int>(heading));
}





