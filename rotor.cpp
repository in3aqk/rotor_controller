
#include "config.h"
#include "rotor.h"
#include <qdebug.h>

Rotor::Rotor()
{
    qDebug() << "init rotot";
    int r = libusb_init(NULL);
    if (r < 0)
    {
        qErrnoWarning("ERROR: failed to initialize libusb (r = %d)\n", r);
    } else {
        this->listDevices();
    }
}


void Rotor::listDevices()
{
    libusb_device **list;
    ssize_t cnt = libusb_get_device_list(NULL, &list);
    if (cnt < 0)
    {
        qErrnoWarning("ERROR: failed to get device list (cnt = %d)\n", cnt);
        return;
    }
    boolean found = false;
    for (ssize_t i = 0; i < cnt; i++) {
        libusb_device *dev = list[i];
        struct libusb_device_descriptor desc;
        int r = libusb_get_device_descriptor(dev, &desc);
        if (r < 0){
            qErrnoWarning("ERROR: failed to get device descriptor (r = %d)\n", r);

        }
        else{

            if (desc.idVendor == VENDOR_ID && desc.idProduct == DEVICE_ID){
                found = true;
                break;
            }

            //qInfo() << desc.idVendor << desc.iProduct << desc.bDeviceProtocol << desc.bDeviceClass;

        }
    }

    if (found) {
        qInfo() << "Relais Board found";
    } else {
        qInfo() << "Relais Board not found";
    }


}

