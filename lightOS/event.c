#include "lightOS.h"
#include <stdio.h>

#ifdef _OS_DEBUG_ON_
#define _OS_EVENT_DEBUG_
#endif

static unsigned int OS_EVENTListCount;
OS_EVENT _os_event_list[OS_EVENT_LIST_LENGTH];

void OS_EVENTInit()
{
    int i;
    OS_EVENTListCount = 0;
}


//return success or fail
OS_EVENT* sendEvent(unsigned int eventType,unsigned int shortMsg,unsigned char broadcast,void *data,unsigned int len)
{
    OS_EVENT *event;
    if (OS_EVENTListCount >= OS_EVENT_LIST_LENGTH){
        return NULL;
    }
    event = &_os_event_list[OS_EVENTListCount];
    event->event_short_inf = shortMsg;
    event->eventType = eventType;
    event->broadcast_flag = broadcast;
    if (data && len>0){
        event->msg = data;
        event->msg_len = len;
    }
    else{
        event->msg = NULL;
        event->msg_len = 0;
    }
    return event;
}

OS_EVENT *getEventFromList(void)
{
    OS_EVENT *e;
    if (OS_EVENTListCount == 0)
    {
        return NULL;
    }

    e = &(_os_event_list[OS_EVENTListCount--]);

#ifdef _OS_DEBUG_ON_
		printf("----OS find a event(type): %u \n",e->eventType);
#endif
    return e;
}
