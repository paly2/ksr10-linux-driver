/*
By paly2
This source code is under the GNU GPL license.

KSR10 Linux Driver main function.
Note : every commands are designed for a "XBox 360 controller" joystick. You can of course change them in this code for your own joystick.
*/

#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include "joystick.h"
#include "robotic_arm.h"

using namespace std;

int main(int argc, char** argv)
{
	Joystick joystick;
	ksr10 arm;
	
	if (!joystick.isFound())
	{
		cout << "Can't find the joystick." << endl;
		return EXIT_FAILURE;
	}
	
	bool led = false;
	while (true)
	{
		// Restrict rate
		usleep(1000);

		// Attempt to sample an event from the joystick
		JoystickEvent event;
		if (joystick.sample(&event))
		{
			// Button 4 : Switch on / off the LED
			if (event.isButton())
			{
				if(event.number == 4) { // Button 4 : control the LED
					if(event.value != 0 && led == false) {
						arm.ctrl(LED, RUN1);
						led = true;
					}
					else if(event.value != 0 && led == true) {
						arm.ctrl(LED, STOP);
						led = false;
					}
				}
				else if(event.number == 5) { // Button 5 : exit the program
					if(event.value != 0)
						return EXIT_SUCCESS;
				}
			}
			else if (event.isAxis())
			{
				if(event.number == 0) { // Axis 0 : control the base
					if(event.value > 10000)
						arm.ctrl(BASE, RUN1);
					else if(event.value < -10000)
						arm.ctrl(BASE, RUN2);
					else
						arm.ctrl(BASE, STOP);
				}
				else if(event.number == 1) { // Axis 1 : control the shoulder
					if(event.value > 10000)
						arm.ctrl(SHOULDER, RUN1);
					else if(event.value < -10000)
						arm.ctrl(SHOULDER, RUN2);
					else
						arm.ctrl(SHOULDER, STOP);
				}
				else if(event.number == 3) { // Axis 2 : control the wrist
					if(event.value > 10000)
						arm.ctrl(WRIST, RUN1);
					else if(event.value < -10000)
						arm.ctrl(WRIST, RUN2);
					else
						arm.ctrl(WRIST, STOP);
				}
				else if(event.number == 4) { // Axis 4 : control the elbow
					if(event.value > 10000)
						arm.ctrl(ELBOW, RUN1);
					else if(event.value < -10000)
						arm.ctrl(ELBOW, RUN2);
					else
						arm.ctrl(ELBOW, STOP);
				}
				else if(event.number == 2 || event.number == 5) { // Axis 2 : close the grip / Axis 5 : open the grip
					if(event.number == 2 && event.value > 10000)
						arm.ctrl(GRIP, RUN1);
					else if(event.number == 5 && event.value > 10000)
						arm.ctrl(GRIP, RUN2);
					else
						arm.ctrl(GRIP, STOP);
				}
			}
		}
	}
}
