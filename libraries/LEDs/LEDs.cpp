#include "LEDs.h"
#include "../lightOS/lightOS.h"

LED_Type led_list[MAX_LED_NUMBER];
int led_count;
OS_TASK *_led_handler;


unsigned int _led_task(int opt);



void LED_init() {
	memset(led_list, 0, sizeof(led_list));
	led_count = 0;
	_led_handler = taskRegister(_led_task, OS_ST_PER_10_MS, 1, 0);
}

int LED_add(int led) {
	int i;
	if (led_count >= MAX_LED_NUMBER) return 0;
	for (i = 0; i < led_count; i++) if (led_list[i].led == led) return 0;
	pinMode(led, OUTPUT);
	led_list[led_count].led = led;
	led_list[led_count].status = 0;
	led_list[led_count].interval = 0;
	led_list[led_count].shift_time = 0;
	led_list[led_count].expire = 0;
	led_count++;
	Serial.println("LED add success !");
	return 1;
}

int LED_run() {
	taskRestart(_led_handler);
}

int _LED_findLED(int led) {
	int i;
	for (i = 0; i < led_count; i++) if (led == led_list[i].led) return i;
	return -1;
}

int LED_status(int led) {
	int i = _LED_findLED(led);
	return led_list[i].function;
}

int LED_blink(int led, unsigned long interval,int sync,unsigned long expire) {
	int i;
	i = _LED_findLED(led);
	if (i < 0) return -1;

	if (sync == -1){
		if (i < 0) return -1;
		led_list[i].shift_time = getSysTime();
		led_list[i].start_time = getSysTime();
		led_list[i].status = 1;
		digitalWrite(led, HIGH);
		led_list[i].interval = interval;
		led_list[i].function = LED_FUNCTION_BLINK;
		led_list[i].expire = expire;
		return 1;
	}
	else{
		int t = _LED_findLED(sync);
		if (led_list[t].function != LED_FUNCTION_BLINK){
			return -1;
		}
		led_list[i].shift_time = led_list[t].shift_time;
		led_list[i].start_time = led_list[t].start_time;
		led_list[i].status = led_list[t].status;
		led_list[i].interval = led_list[t].interval;
		led_list[i].function = led_list[t].function;
		if (expire == 0)
			led_list[i].expire = led_list[t].expire;
		else 
		led_list[i].expire = expire;
		return 1;
	}
}

int LED_on(int led,unsigned long expire) {
	int i;
	i = _LED_findLED(led);
	if (i < 0) return 0;
	led_list[i].shift_time = getSysTime();
	led_list[i].start_time = getSysTime();
	led_list[i].status = 1;
	digitalWrite(led, HIGH);
	led_list[i].interval = 0;
	led_list[i].function = LED_FUNCTION_ON;
	led_list[i].expire = expire;
	Serial.println("LED turned on !");
	return 1;
}

int LED_off(int led) {
	int i;
	i = _LED_findLED(led);
	if (i < 0) return 0;
	led_list[i].shift_time = 0;
	led_list[i].status = 0;
	digitalWrite(led, LOW);
	led_list[i].interval = 0;
	led_list[i].function = LED_FUNCTION_IDEL;
	led_list[i].expire = 0;
	return 1;
}

void LED_offAll() {
	int i;
	for (i = 0; i < led_count; i++) {
		if (led_list[i].led == 0) continue;
		led_list[i].shift_time = 0;
		led_list[i].status = 0;
		digitalWrite(led_list[i].led, LOW);
		led_list[i].interval = 0;
		led_list[i].function = LED_FUNCTION_IDEL;
		led_list[i].expire = 0;
	}
}

unsigned int _led_task(int opt) {
	int i;
	//Serial.print("e");
	for (i = 0; i < led_count; i++) {
		if (led_list[i].led == 0 || led_list[i].function == LED_FUNCTION_IDEL) continue;
		if (led_list[i].expire > 0) {
			if (getSysTime() - led_list[i].start_time >= led_list[i].expire) {
				// expired, turn off
				led_list[i].shift_time = 0;
				led_list[i].status = 0;
				digitalWrite(led_list[i].led, LOW);
				led_list[i].interval = 0;
				led_list[i].function = LED_FUNCTION_IDEL;
				led_list[i].expire = 0;
			}
		}
		if (led_list[i].function == LED_FUNCTION_BLINK) {
			if (getSysTime() - led_list[i].shift_time >= led_list[i].interval) {
				// expired, turn off
				led_list[i].shift_time = getSysTime();
				if (led_list[i].status == 0) led_list[i].status = 1;
				else led_list[i].status = 0;
				digitalWrite(led_list[i].led, led_list[i].status);
			}
		}
	}
}
