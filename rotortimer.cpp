#include "defines.h"
#include "rotortimer.h"
#include <QDebug>
#include <QTimer>


RotorTimer::RotorTimer()
{
    initRotationTimer();
}



void RotorTimer::initRotationTimer()
{
    // create a timer
    timer = new QTimer(this);
    // setup signal and slot
    connect(timer, SIGNAL(timeout()),this, SLOT(rotationTimerSlot()));
    directionSign = 1;
}

void RotorTimer::setRate(qfloat16 rotationTime){
    rate = rotationTime/360*1000; //Time rotate 1 degree
    qInfo() << "setRate" << rate << rotationTime;
}



void RotorTimer::timerGo(qint16 direction){    
    if(direction == DIRECTION_CW){
        directionSign = 1;
    } else{
        directionSign = -1;
    }
    // msec
    timer->start(rate);

}

void RotorTimer::timerGoPreset(){
    if(heading < preset_heading){
        directionSign = 1;
    } else{
        directionSign = -1;
    }
    // msec
    timer->start(rate);
}


void RotorTimer::timerStop(){
    timer->stop();
}


void RotorTimer::rotationTimerSlot(){
    if (rotationType == ROTATION_FREE) {
        if (heading < 360 && directionSign == 1){

            heading = heading + directionSign;
            emit display_heading_sig(heading);
        }
        else if (heading > 0 && directionSign == -1){
            heading = heading + directionSign;
            emit display_heading_sig(heading);
        }
        else {
            qInfo() << "Rotor dead end";
        }
    }
    if (rotationType == ROTATION_PRESET) {
        if (heading < 360 && directionSign == 1 && heading < preset_heading){
            rotor.rotate(DIRECTION_CW,ROTATE_ON);
            rotor.rotate(DIRECTION_CCW,ROTATE_OFF);
            heading = heading + directionSign;
            emit display_heading_sig(heading);
        }
        else if (heading > 0 && directionSign == -1 && heading > preset_heading){
            rotor.rotate(DIRECTION_CCW,ROTATE_ON);
            rotor.rotate(DIRECTION_CW,ROTATE_OFF);
            heading = heading + directionSign;
            emit display_heading_sig(heading);            
        }
        else {
            rotor.rotate(DIRECTION_CW,ROTATE_OFF);
            rotor.rotate(DIRECTION_CCW,ROTATE_OFF);
            timerStop();
            qInfo() << "Preset reached";
        }
    }
}




