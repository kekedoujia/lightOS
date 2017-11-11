# lightOS
Task manager for Mico-Processer projects

Notes:

Before use the library, you need to follow the instructions to do some simple changes for making it match your platform.

In the main.c file : 
You need set up a hardware timer for lightOS, so that lightOS can manages the time delay for your applications.
Set the interrupt every 1ms or 5ms( any time you want, 5ms is for the demo of the code), 
Include lightOS.h and call _light_os_auto_plus() in the timer interrupt function.
If you are using Arduino platform, please uncommon the "#define _Arduino_Platform_Application_"

In os_setup.h file:
Config the time definitions(if you changed the interruption interval you need to modify this part), the demo one is based on 5ms. 
Setup the number of TASK you will have in the application to OS_TASK_LIST_LENGTH. You can keep it as a higher value, but it takes a little bit more memory space.

After that , you can enjoy with lightOS.

In libraries folder, there are some libraries impliment base on lightOS.

LEDs -- Provides mutiple led functions, allow users to control each of these LEDs. LED can blink individuly blinks on its own         frequency.

SerialInput -- A library handles the Serial input. It calls user's callback function automatically, after it detected a user                     specify header and end in the stream. 

ButtonMonitor -- A library can detects short press and long press, gives user a event through callback function.


The demo is implement on Arduino IDE for ArduinoUNO.

