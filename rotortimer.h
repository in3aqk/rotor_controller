#ifndef ROTORTIMER_H
#define ROTORTIMER_H

#include "config.h"
#include <QTimer>
#include <QtGlobal>
#include <QFloat16>

class RotorTimer: public QObject
{

    Q_OBJECT

public:

    RotorTimer();
    qfloat16 heading;
    qint16 preset_heading;
    void initRotationTimer();
    void timerGo(qint16);
    void timerStop();
    void setRate(qfloat16);

private:
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
