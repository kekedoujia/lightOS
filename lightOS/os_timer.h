#ifndef LIGHTOS_OS_TIMER_H_
#define LIGHTOS_OS_TIMER_H_

#include <limits.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define MAX_OS_TIMER_COUNT ULONG_MAX

#ifndef LIGHT_OS_USING_EXTERNAL_TIMER
void os_timer_init(void);
void _system_time_auto_plus(void);
#endif

unsigned long os_get_time(void);
void os_delay(unsigned long timestamp);

#ifdef __cplusplus
}
#endif

#endif  // LIGHTOS_OS_TIMER_H_
