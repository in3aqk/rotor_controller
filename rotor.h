#ifndef ROTOR_H
#define ROTOR_H

#include <libusb.h>


class Rotor
{
    public:
        Rotor();

    protected:
        void listDevices();
};

#endif // ROTOR_H
