#ifndef LIGHTOS_LIBRARIES_BUTTON_MONITOR_PLATFORM_H_
#define LIGHTOS_LIBRARIES_BUTTON_MONITOR_PLATFORM_H_

#ifdef __cplusplus
extern "C" {
#endif

void button_platform_init_input_pullup(int pin);
int button_platform_read(int pin);

#ifdef __cplusplus
}
#endif

#endif  // LIGHTOS_LIBRARIES_BUTTON_MONITOR_PLATFORM_H_
