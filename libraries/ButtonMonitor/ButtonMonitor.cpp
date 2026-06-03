#include "ButtonMonitor.h"

#include "ButtonMonitorPlatform.h"
#include "../../lightOS/lightOS.h"

#include <stddef.h>
#include <string.h>

static ButtonState button_list[BUTTON_NUMBER];
static int button_count;
static OsTask *button_task;
static ButtonEventCallback button_callback = NULL;

static unsigned int button_monitoring_task(int opt);

void button_init(ButtonEventCallback callback) {
  button_count = 0;
  memset(button_list, 0, sizeof(button_list));
  button_callback = callback;
  button_task =
      task_register(button_monitoring_task, OS_ST_PER_1_MS, TASK_RUN, 0);
}

int button_add_pin(int pin) {
  int i;

  if (button_count >= BUTTON_NUMBER) {
    return 0;
  }
  for (i = 0; i < button_count; i++) {
    if (pin == button_list[i].button) {
      return 0;
    }
  }

  button_platform_init_input_pullup(pin);
  button_list[button_count].button = pin;
  button_list[button_count].event_publish = 0;
  button_list[button_count].pre_status = 0;
  button_list[button_count].status = 0;
  button_list[button_count].shift_time = 0;
  button_count++;
  return 1;
}

void button_remove_pin(int pin) {
  int i;
  int j;

  for (i = 0; i < button_count; i++) {
    if (pin != button_list[i].button) {
      continue;
    }

    for (j = i; j < button_count - 1; j++) {
      button_list[j] = button_list[j + 1];
    }
    memset(&button_list[button_count - 1], 0, sizeof(ButtonState));
    button_count--;
    return;
  }
}

void button_run(void) { task_restart(button_task); }

static unsigned int button_monitoring_task(int opt) {
  int i;
  (void)opt;

  for (i = 0; i < button_count; i++) {
    button_list[i].pre_status = button_list[i].status;
    button_list[i].status =
        button_platform_read(button_list[i].button) == 1 ? 0 : 1;

    if (button_list[i].status == 1 && button_list[i].pre_status == 0 &&
        button_list[i].event_publish == 0) {
      button_list[i].pre_status = 1;
      button_list[i].shift_time = os_get_time();
    } else if (button_list[i].status == 1 &&
               button_list[i].pre_status == 1 &&
               button_list[i].event_publish == 0) {
      if (os_get_time() - button_list[i].shift_time >= BUTTON_LONG_PRESS_TH) {
        button_list[i].event_publish = 1;
        if (button_callback != NULL) {
          button_callback(button_list[i].button, BUTTON_EVENT_LONG_PRESS);
        }
        button_list[i].shift_time = 0;
        button_list[i].pre_status = 0;
      }
    } else if (button_list[i].status == 0 &&
               button_list[i].pre_status == 1 &&
               button_list[i].event_publish == 0) {
      if (os_get_time() - button_list[i].shift_time >= BUTTON_SHORT_PRESS_TH) {
        button_list[i].event_publish = 1;
        if (button_callback != NULL) {
          button_callback(button_list[i].button, BUTTON_EVENT_SHORT_PRESS);
        }
      }
      button_list[i].shift_time = 0;
      button_list[i].pre_status = 0;
    } else if (button_list[i].status == 0 &&
               button_list[i].event_publish == 1) {
      button_list[i].event_publish = 0;
      button_list[i].shift_time = 0;
      button_list[i].pre_status = 0;
    }
  }
  return 1;
}

void button_interrupt_handler(void) { task_next_duty_delay(button_task, 0); }
