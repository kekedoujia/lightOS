#include "lightOS.h"

void os_setup(void) {
#ifndef LIGHT_OS_USING_EXTERNAL_TIMER
  os_timer_init();
#endif

  os_event_init();
  os_event_handler_init();

#ifdef _WATCH_DOG_ENABLE_
  watchdog_init();
#endif

  task_init();
}

void os_run(void) {
  while (1) {
    os_task_process();
    os_event_handler_process();

#ifdef _WATCH_DOG_ENABLE_
    watchdog_feed();
#endif
  }
}

void os_run_non_blocking(void) {
  os_task_process();
  os_event_handler_process();
}
