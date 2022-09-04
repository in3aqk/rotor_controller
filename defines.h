#ifndef DEFINES_H
#define DEFINES_H


#define USB_CFG_VENDOR_ID       0x16c0 /* 5824 = voti.nl */
#define USB_CFG_DEVICE_ID       0x05DF /* obdev's shared PID for HIDs */
#define USB_RELAY_VENDOR_NAME     "www.dcttech.com"
#define USB_RELAY_NAME_PREF       "USBRelay"  // + number
#define USB_RELAY_ID_STR_LEN      5 /* length of "unique serial number" in the devices */


#define DIRECTION_CW 1
#define DIRECTION_CCW 2
#define ROTATE_OFF 0
#define ROTATE_ON 1
#define ROTATION_UNSET 0 // Rotate type not set
#define ROTATION_FREE 1 // Rotate by buttons
#define ROTATION_PRESET 2 // Rotate by preset headings


#endif // DEFINES_H
