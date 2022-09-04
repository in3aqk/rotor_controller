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
    initAll();

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


    //qInfo() << "Rotation time: " << settings.value("ROTOR/rotation_time").toInt();
    //qInfo() << "Last position: " << settings.value("ROTOR/last_position").toInt();

    QSettings settings("config.ini", QSettings::IniFormat);
    rotation_time = settings.value("ROTOR/rotation_time").toFloat();
    last_position = settings.value("ROTOR/last_position").toFloat();
    isCalibrated = settings.value("ROTOR/is_calibrated").toInt();


    ui->lcdAzimut->display(static_cast<int>(last_position));

    qInfo()<< "Is calibrated" << isCalibrated;
    if (isCalibrated == 0){
        qInfo() << "Not calibrated";
    } else {
        qInfo() << "Calibrated";
    }

    rotorTimer.setRate(rotation_time);
    rotorTimer.heading = last_position;
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

    connect(ui->btnGo, &QPushButton::released, this, &MainWindow::set);
    connect(ui->btnStop, &QPushButton::released, this, &MainWindow::stop);
    connect(ui->btnReset, &QPushButton::released, this, &MainWindow::reset);

    connect(ui->btn360, &QPushButton::released, this, &MainWindow::set360);
    connect(ui->btn45, &QPushButton::released, this, &MainWindow::set45);
    connect(ui->btn90, &QPushButton::released, this, &MainWindow::set90);
    connect(ui->btn135, &QPushButton::released, this, &MainWindow::set135);
    connect(ui->btn180, &QPushButton::released, this, &MainWindow::set180);
    connect(ui->btn225, &QPushButton::released, this, &MainWindow::set225);
    connect(ui->btn270, &QPushButton::released, this, &MainWindow::set270);
    connect(ui->btn315, &QPushButton::released, this, &MainWindow::set315);


    connect(&rotorTimer, SIGNAL(display_heading_sig(qfloat16)), this, SLOT(display_heading_slot(qfloat16)));
}


void MainWindow::cwPress()
{
    //qInfo()<< "cwPress";
    rotor.rotate(DIRECTION_CW,ROTATE_ON);
    rotor.rotate(DIRECTION_CCW,ROTATE_OFF);
    rotorTimer.timerGo(DIRECTION_CW);
    rotorTimer.rotationType = ROTATION_FREE;

}
void MainWindow::cwRelease()
{
    //qInfo()<< "cwRelease";
    rotor.rotate(DIRECTION_CW,ROTATE_OFF);
    rotor.rotate(DIRECTION_CCW,ROTATE_OFF);
    rotorTimer.timerStop();
    saveLastPosition();
    rotorTimer.rotationType = ROTATION_UNSET;
}

void MainWindow::ccwPress()
{
    //qInfo()<< "ccwPress";
    rotor.rotate(DIRECTION_CCW,ROTATE_ON);
    rotor.rotate(DIRECTION_CW,ROTATE_OFF);
    rotorTimer.timerGo(DIRECTION_CCW);
    rotorTimer.rotationType = ROTATION_FREE;
}
void MainWindow::ccwRelease()
{
    //qInfo()<< "ccwRelease";
    rotor.rotate(DIRECTION_CCW,ROTATE_OFF);
    rotor.rotate(DIRECTION_CW,ROTATE_OFF);
    rotorTimer.timerStop();
    saveLastPosition();
    rotorTimer.rotationType = ROTATION_UNSET;
}

void MainWindow::stop(){
    rotorTimer.rotationType = ROTATION_UNSET;
    rotorTimer.timerStop();
    rotor.stop();
}

void MainWindow::set(){
    rotorTimer.rotationType = ROTATION_PRESET;
}

void MainWindow::reset(){
    rotorTimer.rotationType = ROTATION_UNSET;
    ui->txtPreset->setText("000");
    ui->lcdAzimut->display(0);
    rotorTimer.timerStop();
    rotorTimer.heading = 0;
    rotorTimer.preset_heading = 0;
    rotor.stop();
}

void MainWindow::setCardinal(uint heading){
    ui->txtPreset->setText(QString::number(heading));
    rotorTimer.preset_heading = heading;
    rotorTimer.rotationType = ROTATION_PRESET;
    rotorTimer.timerGoPreset();
}



void MainWindow::set360(){
    setCardinal(360);
}

void MainWindow::set45(){
    setCardinal(45);
}

void MainWindow::set90(){
    setCardinal(90);
}

void MainWindow::set135(){
    setCardinal(135);
}

void MainWindow::set180(){
    setCardinal(180);
}

void MainWindow::set225(){
    setCardinal(225);
}

void MainWindow::set270(){
    setCardinal(270);
}

void MainWindow::set315(){
    setCardinal(315);
}


void MainWindow::saveLastPosition(){
    QSettings settings("config.ini", QSettings::IniFormat);
    settings.setValue("ROTOR/last_position", last_position);
    //dbg(settings.status());
    //qInfo() << "last_pos_release" << last_position;
}


void MainWindow::display_heading_slot(qfloat16 heading){
    last_position = heading;
    ui->lcdAzimut->display(static_cast<int>(heading));
}





