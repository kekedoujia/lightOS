#include "ButtonMonitorPlatform.h"

#include "../../lightOS/os_config.h"

#ifdef _Arduino_Platform_Application_
#if ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

void button_platform_init_input_pullup(int pin) { pinMode(pin, INPUT_PULLUP); }

int button_platform_read(int pin) { return digitalRead(pin); }
#endif
