/*
By paly2
This source code is under the GNU GPL license.

KSR10 linux driver class source code.
*/

#include <iostream>
#include <libusb-1.0/libusb.h>
#include <cstdlib>
#include "robotic_arm.h"

using namespace std;

ksr10::ksr10() {
	for(int i = 0 ; i < 6 ; i++)
		stat[i] = STOP;
	int r = libusb_init(NULL);
	if (r < 0)
		exit(r);
	dh = libusb_open_device_with_vid_pid(NULL, 0x1267, 0x0000);
	if (dh == NULL) {
		cout << "Can't get the KSR10 device handler. Is the KSR10 connected, is it on and do you have root privileges ?" << endl;
		exit(EXIT_FAILURE);
	}
}

int ksr10::ctrl(command cmd, status nstatus) {
	if(cmd == LED && nstatus == RUN2) {
		cout << "The LED can't have the RUN2 status (STOP = light off, RUN1 = light on)." << endl;
		return -1;
	}
	unsigned char bytes[3] = {0};
	stat[cmd] = nstatus;
	bytes[0] = stat[SHOULDER]*64 + stat[ELBOW]*16 + stat[WRIST]*4 + stat[GRIP];
	bytes[1] = stat[BASE];
	bytes[2] = stat[LED];
	return libusb_control_transfer(dh, 0x40, 6, 0x100, 0, bytes, sizeof(bytes), 1000);
}

ksr10::~ksr10() {
	libusb_close(dh);
	libusb_exit(NULL);		
}
