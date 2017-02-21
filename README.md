# lightOS
Task manager for Mico-Processer projects

Notes:

Before use the library, you need to follow the instructions to do some simple changes for making it match your platform.

In your main.c file : 
You need set up a hardware timer for lightOS, so that lightOS can manages the time delay for your applications.
Set the interrupt every 5ms( any time you want, 5ms is for the demo of the code), 
Include lightOS.h and call _light_os_auto_plus() _; in the timer interruption function.

In os_setup.h file:
Config the time definitions(if you changed the interruption interval you need to modify this part), the demo one is based on 5ms. 
Setup the number of TASK you will implement in the application to OS_TASK_LIST_LENGTH. You can keep it as a higher value, but it takes a little bit more memory space.

After that , you can enjoy with lightOS.

The demo is implement on Arduino IDE for ArduinoUNO.

