#ifndef ROTORTIMER_H
#define ROTORTIMER_H


#include <QTimer>
#include <QtGlobal>
#include <QFloat16>

class RotorTimer: public QObject
{

    Q_OBJECT

public:

    RotorTimer();
    float heading;

    void initRotationTimer();
    void timerGo(qint16);
    void timerStop();

private:
    QTimer *timer;
    qfloat16 rate;
    qfloat16 directionSign;


signals:
    void display_heading_sig(qfloat16);

private slots:
    void rotationTimerSlot();


};

#endif // ROTORTIMER_H