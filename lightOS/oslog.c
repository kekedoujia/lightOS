#include "oslog.h"

#include <stddef.h>

static LogCallback log_callback;

void os_log_set_callback(LogCallback callback) { log_callback = callback; }

void os_log(char *log) {
#ifdef _OS_LOG_ENABLE_
  if (log_callback != NULL) {
    log_callback(log);
  }
#else
  (void)log;
#endif
}
