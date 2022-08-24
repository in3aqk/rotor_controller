#ifndef ROTOR_H
#define ROTOR_H

#include "config.h"
#include "defines.h"
#include <qglobal.h>


#define printerr(fmt, ...) fprintf(stderr, fmt, ## __VA_ARGS__);

//#include "hiddata.h"


class Rotor
{
public:
    Rotor();
    qint8 rotate(int direction, int rotate);

protected:

    bool initBoard();
    void timerSlot();

};

#endif // ROTOR_H
