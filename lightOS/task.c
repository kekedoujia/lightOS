#include "lightOS.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static OsTask os_task_list[OS_TASK_LIST_LENGTH];
static unsigned char os_task_status[OS_TASK_LIST_LENGTH];
static OsTask *current_running_task;
static unsigned int task_count;
static OsTask *current_task;

void task_init(void) {
  current_task = NULL;
  task_count = 0;
  memset(os_task_list, 0, sizeof(os_task_list));
  memset(os_task_status, 0, sizeof(os_task_status));
  current_running_task = NULL;
}

OsTask *task_register(unsigned int (*task_callback)(int opt),
                      unsigned long interval, unsigned char status,
                      long temp_interval) {
  OsTask *new_task;
#ifdef _OS_LOG_ENABLE_
  char log[50];
#endif

  if (task_callback == NULL || task_count >= OS_TASK_LIST_LENGTH) {
    return NULL;
  }

  new_task = &os_task_list[task_count];
  new_task->task_callback = task_callback;
  new_task->interval_time = interval;
  new_task->task_num = task_count;
  new_task->task_status = status;
  new_task->last_run_time = os_get_time();
  new_task->temp_interval_time = temp_interval;
  os_task_status[task_count] = 1;

#ifdef _OS_LOG_ENABLE_
  sprintf(log, "add task: %d\n", new_task->task_num);
  os_log(log);
  sprintf(log, "task number: %d status : %d\n", new_task->task_num,
          new_task->task_status);
  os_log(log);
#endif

  task_count++;
  return new_task;
}

void task_restart(OsTask *task) {
  if (task == NULL) {
    return;
  }
  task->task_status = TASK_RUN;
}

void task_pause(OsTask *task) {
  if (task == NULL) {
    return;
  }
  task->task_status = TASK_IDLE;
}

void task_next_duty_delay(OsTask *task, long interval) {
  if (task == NULL) {
    return;
  }
  task->temp_interval_time = interval;
  task->last_run_time = os_get_time();
  task_restart(task);
}

void self_next_duty_delay(long interval) {
  if (current_task == NULL) {
    return;
  }
  current_task->temp_interval_time = interval;
}

OsTask *task_self_handler(void) { return current_running_task; }

void os_task_process(void) {
  unsigned int i;
  unsigned long delta;
  unsigned long interval;
  unsigned long time_now;
  OsTask *task;

  for (i = 0; i < task_count; i++) {
    if (os_task_status[i] != 1) {
      continue;
    }

    task = &os_task_list[i];
    if (task->task_status != TASK_RUN) {
      continue;
    }

    if (task->temp_interval_time >= 0) {
      interval = task->temp_interval_time;
    } else {
      interval = task->interval_time;
    }

    time_now = os_get_time();
    delta = time_now - task->last_run_time;
    if (delta < interval) {
      continue;
    }

    task->temp_interval_time = -1;
    current_running_task = task;
    task->last_run_time = os_get_time();
    current_task = task;
    task->task_callback(0);
    current_task = NULL;
    current_running_task = NULL;

#ifdef _WATCH_DOG_ENABLE_
    watchdog_feed();
#endif
  }
}
