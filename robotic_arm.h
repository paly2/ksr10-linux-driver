/*
By paly2
This source code is under the GNU GPL license.

KSR10 linux driver library header.
*/

#include <libusb-1.0/libusb.h>

enum command {  SHOULDER = 0, ELBOW = 1, WRIST = 2, GRIP = 3, BASE = 4, LED = 5};
enum status { STOP = 0, RUN1 = 1, RUN2 = 2}; // Note : the LED can't have the RUN2 status.

class ksr10 {
	public:
	
	ksr10();
	~ksr10();
	int ctrl(command cmd, status nstatus);
	
	private:
	
	libusb_device_handle* dh;
	status stat[6];
};
