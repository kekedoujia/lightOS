#pragma once
#ifndef __LED_DRIVER__
#define __LED_DRIVER__

#if ARDUINO >= 100
#include <Arduino.h>
#include "avr/pgmspace.h" // new include
#else
#include <WProgram.h>
#include "avr/pgmspace.h" // new include
#endif

#include "TrapperConfig.h"

#ifndef MAX_LED_NUMBER
#define MAX_LED_NUMBER			5
#endif

#define LED_FUNCTION_IDEL		0
#define LED_FUNCTION_ON			1
#define LED_FUNCTION_BLINK		3


typedef struct {
	int led;
	char status;
	char function;
	unsigned long interval;
	unsigned long shift_time;
	unsigned long expire;
	unsigned long start_time;
} LED_Type;

void LED_init();
int LED_run();
int LED_add(int led);
int LED_blink(int led, unsigned long interval, int sync, unsigned long expire);
int LED_status(int led);
int LED_on(int led, unsigned long expire);
int LED_off(int led);
void LED_offAll();


#endif // !__LED_DRIVER__