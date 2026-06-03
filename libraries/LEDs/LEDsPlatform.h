#ifndef LIGHTOS_LIBRARIES_LEDS_PLATFORM_H_
#define LIGHTOS_LIBRARIES_LEDS_PLATFORM_H_

#ifdef __cplusplus
extern "C" {
#endif

#define LED_PLATFORM_LOW 0
#define LED_PLATFORM_HIGH 1

void led_platform_init_output(int pin);
void led_platform_write(int pin, int value);
void led_platform_log(const char *message);

#ifdef __cplusplus
}
#endif

#endif  // LIGHTOS_LIBRARIES_LEDS_PLATFORM_H_
