#ifndef ROTOR_H
#define ROTOR_H

#define USB_CFG_VENDOR_ID       0x16c0 /* 5824 = voti.nl */
#define USB_CFG_DEVICE_ID       0x05DF /* obdev's shared PID for HIDs */
#define USB_RELAY_VENDOR_NAME     "www.dcttech.com"
#define USB_RELAY_NAME_PREF       "USBRelay"  // + number
#define USB_RELAY_ID_STR_LEN      5 /* length of "unique serial number" in the devices */


#define DIRECTION_CW 1
#define DIRECTION_CCW 2
#define ROTATE_OFF 0
#define ROTATE_ON 1

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

};

#endif // ROTOR_H
