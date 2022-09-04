#ifndef ROTORTIMER_H
#define ROTORTIMER_H

#include "config.h"
#include <QTimer>
#include <QtGlobal>
#include <QFloat16>
#include "rotor.h"

class RotorTimer: public QObject
{

    Q_OBJECT

public:

    RotorTimer();
    qfloat16 heading;
    qint16 preset_heading;
    quint8 rotationType;
    void initRotationTimer();
    void timerGo(qint16);
    void timerGoPreset();
    void timerStop();
    void setRate(qfloat16);

private:
    Rotor rotor;
    QTimer *timer;
    qfloat16 rate;
    qfloat16 directionSign;
    qfloat16 rotation_time;


signals:
    void display_heading_sig(qfloat16);

private slots:
    void rotationTimerSlot();


};

#endif // ROTORTIMER_H
