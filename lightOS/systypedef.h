#ifndef LIGHTOS_SYSTYPEDEF_H_
#define LIGHTOS_SYSTYPEDEF_H_

typedef struct {
  unsigned int task_num;
  unsigned char task_status;
  unsigned long last_run_time;
  unsigned long interval_time;
  long temp_interval_time;
  unsigned int (*task_callback)(int opt);
} OsTask;

typedef struct {
  unsigned int event_type;
  unsigned int event_short_inf;
  unsigned char broadcast_flag;
  void *msg;
  unsigned int msg_len;
} OsEvent;

typedef struct {
  unsigned int handle_num;
  unsigned char handle_status;
  unsigned int event_type;
  void (*handler_callback)(OsEvent *event);
} OsEventHandler;

#endif  // LIGHTOS_SYSTYPEDEF_H_
