#include "os_timer.h"

#include "os_config.h"

#ifdef _Arduino_Platform_Application_
#if ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

unsigned long os_get_time(void) { return millis(); }

#endif
