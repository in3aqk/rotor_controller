#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "config.h"
#include <QMainWindow>
#include <QDebug>
#include <QSettings>
#include <QTimer>
#include "rotor.h"
#include "rotortimer.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE




class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

private:
    Rotor rotor;
    RotorTimer rotorTimer;


    Ui::MainWindow *ui;
    void initAll();
    void allOff();
    void setEvents();
    void cwPress();
    void cwRelease();
    void ccwPress();
    void ccwRelease();
    void stop();
    void set();
    void reset();
    void setCardinal(uint);
    void set360();
    void set45();
    void set90();
    void set135();
    void set180();
    void set225();
    void set270();
    void set315();
    void saveLastPosition();
    int rotation_time;
    float last_position;
    int isCalibrated;

public slots:
    void display_heading_slot(qfloat16);


};
#endif // MAINWINDOW_H
