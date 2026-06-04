#ifndef LIGHTOS_LIBRARIES_BUTTON_MONITOR_H_
#define LIGHTOS_LIBRARIES_BUTTON_MONITOR_H_

#include "../../lightOS/os_config.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef BUTTON_NUMBER
#define BUTTON_NUMBER 5
#endif

#ifndef BUTTON_SHORT_PRESS
#define BUTTON_SHORT_PRESS_TH (OS_ST_PER_10_MS * 5)
#endif

#ifndef BUTTON_LONG_PRESS
#define BUTTON_LONG_PRESS_TH (OS_ST_PER_100_MS * 30)
#endif

#define BUTTON_EVENT_SHORT_PRESS 1
#define BUTTON_EVENT_LONG_PRESS 2

typedef void (*ButtonEventCallback)(int button, int event);

typedef struct {
  int button;
  char pre_status;
  char status;
  char event_publish;
  unsigned long shift_time;
} ButtonState;

void button_init(ButtonEventCallback callback);
int button_add_pin(int pin);
void button_remove_pin(int pin);
void button_run(void);
void button_interrupt_handler(void);

#ifdef __cplusplus
}
#endif

#endif  // LIGHTOS_LIBRARIES_BUTTON_MONITOR_H_
