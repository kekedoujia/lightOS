#ifndef LIGHTOS_EVENT_H_
#define LIGHTOS_EVENT_H_

#include "os_config.h"
#include "systypedef.h"

#ifdef __cplusplus
extern "C" {
#endif

#define OS_EVENT_TYPE 0x0000
#define APP_EVENT_TYPE 0x4000
#define EVENT_BROAD_CAST_BIT 0x2000

void os_event_init(void);
OsEvent *os_event_send(unsigned int event_type, unsigned int short_msg,
                       unsigned char broadcast, void *data, unsigned int len);
OsEvent *os_event_pop(void);

#ifdef __cplusplus
}
#endif

#endif  // LIGHTOS_EVENT_H_
