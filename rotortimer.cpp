#include "defines.h"
#include "rotortimer.h"
#include <QDebug>
#include <QTimer>


RotorTimer::RotorTimer()
{
    qDebug() << "Constructor";
    initRotationTimer();
}



void RotorTimer::initRotationTimer()
{


    qInfo()<< "Ïnit rotation timer";
    // create a timer
    timer = new QTimer(this);

    // setup signal and slot
    connect(timer, SIGNAL(timeout()),this, SLOT(rotationTimerSlot()));
    rate = (qfloat16)1;



}

void RotorTimer::timerGo(qint16 direction){
    // msec
    timer->start(1000);
    if(direction == DIRECTION_CW){
        directionSign = (qfloat16)1;
    } else {
        directionSign = (qfloat16)-1;
    }
}

void RotorTimer::timerStop(){
    timer->stop();
}



void RotorTimer::rotationTimerSlot(){
    heading += rate*directionSign;
    qDebug() << "position..." << heading;
    emit display_heading_sig(heading);
}




