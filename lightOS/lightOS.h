#ifndef LIGHTOS_LIGHTOS_H_
#define LIGHTOS_LIGHTOS_H_

#include "event.h"
#include "handle.h"
#include "os_config.h"
#include "os_timer.h"
#include "oslog.h"
#include "osmemory.h"
#include "systypedef.h"
#include "task.h"
#include "watchdog.h"

#ifdef __cplusplus
extern "C" {
#endif

void os_setup(void);
void os_run(void);
void os_run_non_blocking(void);

#ifdef __cplusplus
}
#endif

#endif  // LIGHTOS_LIGHTOS_H_
