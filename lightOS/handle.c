#include "lightOS.h"

#include <stdio.h>
#include <string.h>

static OsEventHandler event_handler_list[OS_HANDLER_LIST_LENGTH];
static unsigned int event_handler_count = 0;

void os_event_handler_init(void) {
  memset(event_handler_list, 0, sizeof(event_handler_list));
  event_handler_count = 0;
}

OsEventHandler *os_event_handler_register(
    void (*handler_callback)(OsEvent *event), unsigned int event_type,
    unsigned char status) {
  unsigned int i;
  OsEventHandler *handler;

  if (handler_callback == NULL) {
    return NULL;
  }

  for (i = 0; i < event_handler_count; i++) {
    handler = &event_handler_list[i];
    if (handler->handler_callback == handler_callback &&
        handler->event_type == event_type) {
      return handler;
    }
  }

  if (event_handler_count >= OS_HANDLER_LIST_LENGTH) {
    return NULL;
  }

  handler = &event_handler_list[event_handler_count];
  handler->handle_num = event_handler_count;
  handler->handler_callback = handler_callback;
  handler->event_type = event_type;
  handler->handle_status = status;
  event_handler_count++;
  return handler;
}

void os_event_handler_enable(unsigned int handler_num) {
  if (handler_num >= event_handler_count) {
    return;
  }
  event_handler_list[handler_num].handle_status = 1;
}

void os_event_handler_disable(unsigned int handler_num) {
  if (handler_num >= event_handler_count) {
    return;
  }
  event_handler_list[handler_num].handle_status = 0;
}

unsigned char os_event_handler_status(unsigned int handler_num) {
  if (handler_num >= event_handler_count) {
    return 0;
  }
  return event_handler_list[handler_num].handle_status;
}

void os_event_handler_process(void) {
  unsigned int i;
#ifdef _OS_LOG_ENABLE_
  char log[100];
#endif
  OsEvent *event;
  OsEventHandler *handler;

  event = os_event_pop();
  while (event != NULL) {
#ifdef _OS_DEBUG_ON_
    printf("----OS  get a event %u\n", event->event_type);
#endif

    for (i = 0; i < event_handler_count; i++) {
      handler = &event_handler_list[i];
      if (handler->handle_status != 1 || handler->event_type != event->event_type) {
        continue;
      }

#ifdef _OS_DEBUG_ON_
      printf("Call event handler: %d    Event type: %d\n---------------------\n",
             handler->handle_num, event->event_type);
#endif
#ifdef _OS_LOG_ENABLE_
      sprintf(log, "Call event handler: %d    Event type: %d\n---------------------\n",
              handler->handle_num, event->event_type);
      os_log(log);
#endif

      handler->handler_callback(event);

#ifdef _WATCH_DOG_ENABLE_
      watchdog_feed();
#endif

      if (event->broadcast_flag <= 0) {
        break;
      }
    }

    if (event->msg != NULL) {
      os_free(event->msg);
      event->msg = NULL;
      event->msg_len = 0;
    }
    event = os_event_pop();
  }
}
