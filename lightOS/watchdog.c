#include "watchdog.h"

static char dog_status;

void watchdog_init(void) { dog_status = 0; }

void watchdog_feed(void) {}

void watchdog_enable(void) { dog_status = 1; }

void watchdog_stop(void) { dog_status = 0; }
