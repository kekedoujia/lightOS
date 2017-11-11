#pragma once
#ifndef __BUTTON_MONITOR__
#define __BUTTON_MONITOR__


#if ARDUINO >= 100
#include <Arduino.h>
#include "avr/pgmspace.h" // new include
#else
#include <WProgram.h>
#include "avr/pgmspace.h" // new include
#endif


#ifndef BUTTON_NUMBER
#define BUTTON_NUMBER	5
#endif // !BUTTION_NUMBER

#ifndef BUTTON_SHORT_PRESS
#define BUTTON_SHORT_PRESS_TH OS_ST_PER_10_MS*5
#endif // !BUTTON_SHORT_PRESS

#ifndef BUTTON_LONG_PRESS
#define BUTTON_LONG_PRESS_TH OS_ST_PER_100_MS*30
#endif // !BUTTON_LONG_PRESS

#define BUTTON_EVENT_SHORT_PRESS		1
#define BUTTON_EVENT_LONG_PRESS			2

typedef void (*Button_Event_Callback)(int, int);

typedef struct _buttontype{
	int button;
	char pre_status;
	char status;
	char event_publish;
	unsigned long shift_time;
} Button_Type;


void Button_init(Button_Event_Callback cb);
int Button_addPin(int pin);
void Button_removePin(int pin);
void Button_run();
//void Button_eventCallback(int button, int event);
void Button_interruptHandler();

#endif // !__BUTTON_MONITOR__
