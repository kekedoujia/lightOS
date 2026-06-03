#include "LEDsPlatform.h"

#include "../../lightOS/os_config.h"

#ifdef _Arduino_Platform_Application_
#if ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

void led_platform_init_output(int pin) { pinMode(pin, OUTPUT); }

void led_platform_write(int pin, int value) {
  digitalWrite(pin, value == LED_PLATFORM_HIGH ? HIGH : LOW);
}

void led_platform_log(const char *message) { Serial.println(message); }
#endif
