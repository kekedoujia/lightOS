#include "event.h"

#include "os_config.h"
#include "osmemory.h"

#include <stdio.h>
#include <string.h>

#ifdef _OS_DEBUG_ON_
#define _OS_EVENT_DEBUG_
#endif

static unsigned int event_count;
static OsEvent event_queue[OS_EVENT_LIST_LENGTH];
static OsEvent current_event;

void os_event_init(void) {
  unsigned int i;

  for (i = 0; i < event_count; i++) {
    if (event_queue[i].msg != NULL) {
      os_free(event_queue[i].msg);
    }
  }

  event_count = 0;
  memset(event_queue, 0, sizeof(event_queue));
  memset(&current_event, 0, sizeof(current_event));
}

OsEvent *os_event_send(unsigned int event_type, unsigned int short_msg,
                       unsigned char broadcast, void *data,
                       unsigned int len) {
  OsEvent *event;

  if (event_count >= OS_EVENT_LIST_LENGTH) {
    return NULL;
  }

  event = &event_queue[event_count];
  if (data != NULL && len > 0) {
    event->msg = os_malloc(len);
    if (event->msg == NULL) {
      return NULL;
    }
    memcpy(event->msg, data, len);
    event->msg_len = len;
  } else {
    event->msg = NULL;
    event->msg_len = 0;
  }

  event->event_short_inf = short_msg;
  event->event_type = event_type;
  event->broadcast_flag = broadcast;
  event_count++;
  return event;
}

OsEvent *os_event_pop(void) {
  if (event_count == 0) {
    return NULL;
  }

  current_event = event_queue[0];
  event_count--;
  if (event_count > 0) {
    memmove(&event_queue[0], &event_queue[1],
            event_count * sizeof(OsEvent));
  }

#ifdef _OS_DEBUG_ON_
  printf("----OS find a event(type): %u \n", current_event.event_type);
#endif

  return &current_event;
}
