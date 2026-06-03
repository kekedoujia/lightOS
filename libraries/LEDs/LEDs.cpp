#include "LEDs.h"

#include "LEDsPlatform.h"
#include "../../lightOS/lightOS.h"

#include <string.h>

static LedState led_list[MAX_LED_NUMBER];
static int led_count;
static OsTask *led_handler;

static int find_led(int led);
static unsigned int led_task(int opt);

void led_init(void) {
  memset(led_list, 0, sizeof(led_list));
  led_count = 0;
  led_handler = task_register(led_task, OS_ST_PER_10_MS, TASK_RUN, 0);
}

int led_add(int led) {
  int i;

  if (led_count >= MAX_LED_NUMBER) {
    return 0;
  }
  for (i = 0; i < led_count; i++) {
    if (led_list[i].led == led) {
      return 0;
    }
  }

  led_platform_init_output(led);
  led_list[led_count].led = led;
  led_list[led_count].status = 0;
  led_list[led_count].interval = 0;
  led_list[led_count].shift_time = 0;
  led_list[led_count].expire = 0;
  led_count++;
  led_platform_log("LED add success !");
  return 1;
}

int led_run(void) {
  task_restart(led_handler);
  return 1;
}

static int find_led(int led) {
  int i;
  for (i = 0; i < led_count; i++) {
    if (led == led_list[i].led) {
      return i;
    }
  }
  return -1;
}

int led_status(int led) {
  int i = find_led(led);
  if (i < 0) {
    return -1;
  }
  return led_list[i].function;
}

int led_blink(int led, unsigned long interval, int sync,
              unsigned long expire) {
  int i = find_led(led);

  if (i < 0) {
    return -1;
  }

  if (sync == -1) {
    led_list[i].shift_time = os_get_time();
    led_list[i].start_time = os_get_time();
    led_list[i].status = 1;
    led_platform_write(led, LED_PLATFORM_HIGH);
    led_list[i].interval = interval;
    led_list[i].function = LED_FUNCTION_BLINK;
    led_list[i].expire = expire;
    return 1;
  }

  int sync_index = find_led(sync);
  if (sync_index < 0 ||
      led_list[sync_index].function != LED_FUNCTION_BLINK) {
    return -1;
  }

  led_list[i].shift_time = led_list[sync_index].shift_time;
  led_list[i].start_time = led_list[sync_index].start_time;
  led_list[i].status = led_list[sync_index].status;
  led_list[i].interval = led_list[sync_index].interval;
  led_list[i].function = led_list[sync_index].function;
  if (expire == 0) {
    led_list[i].expire = led_list[sync_index].expire;
  } else {
    led_list[i].expire = expire;
  }
  return 1;
}

int led_on(int led, unsigned long expire) {
  int i = find_led(led);
  if (i < 0) {
    return 0;
  }

  led_list[i].shift_time = os_get_time();
  led_list[i].start_time = os_get_time();
  led_list[i].status = 1;
  led_platform_write(led, LED_PLATFORM_HIGH);
  led_list[i].interval = 0;
  led_list[i].function = LED_FUNCTION_ON;
  led_list[i].expire = expire;
  led_platform_log("LED turned on !");
  return 1;
}

int led_off(int led) {
  int i = find_led(led);
  if (i < 0) {
    return 0;
  }

  led_list[i].shift_time = 0;
  led_list[i].status = 0;
  led_platform_write(led, LED_PLATFORM_LOW);
  led_list[i].interval = 0;
  led_list[i].function = LED_FUNCTION_IDLE;
  led_list[i].expire = 0;
  return 1;
}

void led_off_all(void) {
  int i;
  for (i = 0; i < led_count; i++) {
    if (led_list[i].led == 0) {
      continue;
    }
    led_list[i].shift_time = 0;
    led_list[i].status = 0;
    led_platform_write(led_list[i].led, LED_PLATFORM_LOW);
    led_list[i].interval = 0;
    led_list[i].function = LED_FUNCTION_IDLE;
    led_list[i].expire = 0;
  }
}

static unsigned int led_task(int opt) {
  int i;
  (void)opt;

  for (i = 0; i < led_count; i++) {
    if (led_list[i].led == 0 ||
        led_list[i].function == LED_FUNCTION_IDLE) {
      continue;
    }

    if (led_list[i].expire > 0 &&
        os_get_time() - led_list[i].start_time >= led_list[i].expire) {
      led_list[i].shift_time = 0;
      led_list[i].status = 0;
      led_platform_write(led_list[i].led, LED_PLATFORM_LOW);
      led_list[i].interval = 0;
      led_list[i].function = LED_FUNCTION_IDLE;
      led_list[i].expire = 0;
    }

    if (led_list[i].function == LED_FUNCTION_BLINK &&
        os_get_time() - led_list[i].shift_time >= led_list[i].interval) {
      led_list[i].shift_time = os_get_time();
      led_list[i].status = led_list[i].status == 0 ? 1 : 0;
      led_platform_write(led_list[i].led, led_list[i].status);
    }
  }
  return 1;
}
