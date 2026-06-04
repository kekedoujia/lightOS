#ifndef LIGHTOS_LIBRARIES_LEDS_H_
#define LIGHTOS_LIBRARIES_LEDS_H_

#ifdef __cplusplus
extern "C" {
#endif

#ifndef MAX_LED_NUMBER
#define MAX_LED_NUMBER 5
#endif

#define LED_FUNCTION_IDLE 0
#define LED_FUNCTION_ON 1
#define LED_FUNCTION_BLINK 3

typedef struct {
  int led;
  char status;
  char function;
  unsigned long interval;
  unsigned long shift_time;
  unsigned long expire;
  unsigned long start_time;
} LedState;

void led_init(void);
int led_run(void);
int led_add(int led);
int led_blink(int led, unsigned long interval, int sync, unsigned long expire);
int led_status(int led);
int led_on(int led, unsigned long expire);
int led_off(int led);
void led_off_all(void);

#ifdef __cplusplus
}
#endif

#endif  // LIGHTOS_LIBRARIES_LEDS_H_
