#include "ButtonMonitor.h"
#include "../lightOS/lightOS.h"


Button_Type button_list[BUTTON_NUMBER];
int button_count;
OS_TASK *button_task;

Button_Event_Callback _button_callback = NULL;


unsigned int _buttonMonitingTask(int opt);

void Button_init(Button_Event_Callback cb) {
	button_count = 0;
	memset(button_list, 0, sizeof(button_list));
	_button_callback = cb;
	button_task = taskRegister(_buttonMonitingTask, OS_ST_PER_1_MS, 1, 0);
}

int Button_addPin(int pin) {
	int i;
	if (button_count >= BUTTON_NUMBER) return 0;
	for (i = 0; i < button_count; i++) {
		if (pin == button_list[i].button) return 0;
	}
	pinMode(pin,INPUT_PULLUP);
	button_list[button_count].button = pin;
	button_list[button_count].event_publish = 0;
	button_list[button_count].pre_status = 0;
	button_list[button_count].status = 0;
	button_list[button_count].shift_time = 0;
	button_count++;
}

void Button_run() {
	taskRestart(button_task);
}

unsigned int _buttonMonitingTask(int opt) {
	int i;
	for (i = 0; i < button_count; i++) {
		button_list[i].pre_status = button_list[i].status;
		char ste = digitalRead(button_list[i].button);
		if (ste==1) button_list[i].status = 0;
		else button_list[i].status = 1;
		if (button_list[i].status == 1 && 
			button_list[i].pre_status == 0 &&
			button_list[i].event_publish == 0) 
		{
			//press down
			button_list[i].pre_status = 1;
			button_list[i].shift_time = getSysTime();
		}
		else if (button_list[i].status == 1 && 
				button_list[i].pre_status == 1 && 
				button_list[i].event_publish == 0) 
			{
			if (getSysTime() - button_list[i].shift_time >= BUTTON_LONG_PRESS_TH) {
				button_list[i].event_publish = 1;
				_button_callback(button_list[i].button, BUTTON_EVENT_LONG_PRESS);
				button_list[i].shift_time = 0;
				button_list[i].pre_status = 0;
				//button_list[i].event_publish = 0;
			}
		}
		else if (button_list[i].status == 0 && 
				button_list[i].pre_status == 1 &&
				button_list[i].event_publish == 0) 
			{
			if (getSysTime() - button_list[i].shift_time >= BUTTON_SHORT_PRESS_TH) {
				button_list[i].event_publish = 1;
				_button_callback(button_list[i].button, BUTTON_EVENT_SHORT_PRESS);
			}
			button_list[i].shift_time = 0;
			button_list[i].pre_status = 0;
			//button_list[i].event_publish = 0;
		}
		else if (button_list[i].status == 0 && button_list[i].event_publish == 1){
			button_list[i].event_publish = 0;
			button_list[i].shift_time = 0;
			button_list[i].pre_status = 0;
		}
	}
}

void Button_interruptHandler(){  //process button task now
	taskNextDutyDelay(button_task,0);
}

