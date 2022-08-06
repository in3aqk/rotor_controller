
#include "config.h"
#include "rotor.h"
#include "usb_relay_device.h"
#include <qdebug.h>
#include <QThread>

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
    }
}

/**
 * Detect if a 2 relay module is present
 * @brief Rotor::is_present
 * @return bool true false
 */
bool Rotor::initBoard(){
    pusb_relay_device_info_t device = usb_relay_device_enumerate();
    qInfo() << device->serial_number;
    if (device->type == 2 && strcmpi(device->serial_number,"HURTM")==0){
        qInfo() << "Two relays module found!";
        handle = usb_relay_device_open(device);
        usb_relay_device_open_one_relay_channel(handle,1);
        QThread::sleep(10);
        usb_relay_device_close_one_relay_channel(handle,1);

        return true;
    } else {
        qInfo() << "Relay module not found";
        return false;
    }
}

