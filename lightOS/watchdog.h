#ifndef LIGHTOS_WATCHDOG_H_
#define LIGHTOS_WATCHDOG_H_

#ifdef __cplusplus
extern "C" {
#endif

void watchdog_init(void);
void watchdog_feed(void);
void watchdog_enable(void);
void watchdog_stop(void);

#ifdef __cplusplus
}
#endif

#endif  // LIGHTOS_WATCHDOG_H_
