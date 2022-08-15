
#include "config.h"
#include "rotor.h"
#include "usb_relay_device.h"
#include <qdebug.h>
#include <QTimer>

/*
 * USES:
 * https://github.com/pavel-a/usb-relay-hid/tree/usb-relay-lib_v2.1
 */

intptr_t handle;


Rotor::Rotor()
{
    qInfo() << "init rotor";
    int res = usb_relay_init();
    qInfo() << "init" << res;
    if (res == 0){
       bool found = initBoard();
       if (!found){
           qInfo() << "Unable to init board";
       }
    } else{
        qInfo() << "Unable to init library";
    }


}

/**
 * Detect if a 2 relay module is present and inits it
 * @brief Rotor::is_present
 * @return bool true false
 */
bool Rotor::initBoard(){
    pusb_relay_device_info_t device = usb_relay_device_enumerate();
    qInfo() << device->serial_number;
    if (device->type == 2 && strcmpi(device->serial_number,"HURTM")==0){
        qInfo() << "Two relays module found!";
        handle = usb_relay_device_open(device);
        return true;
    } else {
        qInfo() << "Relay module not found";
        return false;
    }
}


/**
 * Send comma to the relay module
 * @brief Rotor::rotate
 * @param direction DIRECTION_CW DIRECTION_CCW
 * @param rotate ROTATE_OFF ROTATE_ON
 * @return command result 0 = success 1 = error
 */
qint8 Rotor::rotate(int direction, int rotate){
    qInfo() << "Relay:" << direction << rotate;
    int result = 0;
    if (rotate == ROTATE_ON){
        result = usb_relay_device_open_one_relay_channel(handle,direction);
    } else if (rotate == ROTATE_OFF){
        result = usb_relay_device_close_one_relay_channel(handle,direction);
    } else{
        result = usb_relay_device_close_one_relay_channel(handle,direction);
    }
    return result;
}


