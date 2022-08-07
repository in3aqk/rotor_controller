#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QSettings>
#include "rotor.h"

#define DIRECTION_CW 1
#define DIRECTION_CCW 2
#define ROTATE_OFF 0
#define ROTATE_ON 1

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
    QSettings settings;
    Ui::MainWindow *ui;
    void initAll();
    void allOff();
    void setEvents();
    void cwPress();
    void cwRelease();
    void ccwPress();
    void ccwRelease();


};
#endif // MAINWINDOW_H
