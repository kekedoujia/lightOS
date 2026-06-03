#ifndef LIGHTOS_HANDLE_H_
#define LIGHTOS_HANDLE_H_

#include "systypedef.h"

#ifdef __cplusplus
extern "C" {
#endif

#define MSG_TYPE_SUPPORT_LENGTH 3

void os_event_handler_init(void);
OsEventHandler *os_event_handler_register(
    void (*handler_callback)(OsEvent *event), unsigned int event_type,
    unsigned char status);
void os_event_handler_enable(unsigned int handler_num);
void os_event_handler_disable(unsigned int handler_num);
unsigned char os_event_handler_status(unsigned int handler_num);
void os_event_handler_process(void);

#ifdef __cplusplus
}
#endif

#endif  // LIGHTOS_HANDLE_H_
