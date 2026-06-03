#ifndef LIGHTOS_TASK_H_
#define LIGHTOS_TASK_H_

#include "os_config.h"
#include "systypedef.h"

#ifdef __cplusplus
extern "C" {
#endif

#define TASK_RUN 1
#define TASK_IDLE 0

void task_init(void);
OsTask *task_register(unsigned int (*task_callback)(int opt),
                      unsigned long interval, unsigned char status,
                      long temp_interval);
void task_next_duty_delay(OsTask *task, long interval);
void self_next_duty_delay(long interval);
void task_restart(OsTask *task);
void task_pause(OsTask *task);
OsTask *task_self_handler(void);
void os_task_process(void);

#ifdef __cplusplus
}
#endif

#endif  // LIGHTOS_TASK_H_
