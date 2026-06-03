#include "lightOS.h"

#ifndef LIGHT_OS_USING_EXTERNAL_TIMER

static unsigned long os_system_time;

void os_timer_init(void) { os_system_time = 0; }

unsigned long os_get_time(void) { return os_system_time; }

void _system_time_auto_plus(void) { os_system_time++; }

#endif

#ifdef _Arduino_Platform_Application_
#include "Arduino.h"

unsigned long os_get_time(void) { return millis(); }

#endif

void os_delay(unsigned long timestamp) {
  unsigned long start = os_get_time();
  while (os_get_time() - start < timestamp) {
  }
}
