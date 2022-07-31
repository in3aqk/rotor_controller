#ifndef CONFIG_H
#define CONFIG_H


#define VENDOR_ID       0x16c0 /* 5824 = voti.nl */
#define DEVICE_ID       0x05DF /* obdev's shared PID for HIDs */
#define RELAY_VENDOR_NAME   "www.dcttech.com"
#define RELAY_NAME_PREF     "USBRelay"  /* can be relay1... relay8 */

#define USB_RELAY_ID_STR_LEN    5 /* length of "unique serial number" in the devices */
#endif // CONFIG_H
