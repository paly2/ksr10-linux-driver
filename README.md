# KSR10 Robotic Arm Linux C++ Driver

This is a (very) small library that allows you to control a KSR10 with C++.

Note : every commands of the demonstration program (in the file `main.cpp`) are designed for a "XBox 360 controller" joystick. You can of course change them in the `main.cpp` file for your own joystick.  
Other note : The joystick library was found [https://github.com/drewnoakes/joystick/](here).

### How to compile it ?

Type these commands in a console :  
`sudo apt-get install libusb-1.0-0-dev`  
`git clone https://github.com/paly2/ksr10-linux-driver`  
`cd ksr10-linux-driver`  
`make`  
`sudo ./ksr10 # To run the program.`  
You can now control the KSR10 with your joystick.

You can also just copy the `robotic_arm.h` and `robotic_arm.cpp` files in your own program to use this driver as a library (see the `Driver API` part).

### Driver API

First, create an instance of ksr10 :  
`ksr10 robotic_arm;`

Then, you can send a control to the KSR10 with :  
`robotic_arm.ctrl(command cmd, status new_status);`

Available commands are :
- `SHOULDER`
- `ELBOW`
- `WRIST`
- `GRIP`
- `BASE`
- `LED`
And available status are :
- `STOP`
- `RUN1`
- `RUN2`
Note : you can't use the `RUN2` status for the LED.

Example :  
`#include <unistd.h>`  
`#include "robotic_arm.h"`  
`int main() {`  
`  ksr10 robotic_arm;`  
`  robotic_arm.ctrl(LED, RUN1);`  
`  robotic_arm.ctrl(ELBOW, RUN1);`  
`  sleep(1);`  
`  robotic_arm.ctrl(ELBOW, STOP);`  
`  robotic_arm.ctrl(LED, STOP);`  
`  robotic_arm.ctrl(ELBOW, RUN2);`  
`  sleep(1);`  
`  robotic_arm.ctrl(ELBOW, STOP);`  
`  return 0;`  
`}`

Important note : at the end of the program, stop all the parts you put in operation.
