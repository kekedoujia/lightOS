#include "lightOS.h"
#include"event.h"
//#include"message.h"
#include"task.h"
#include"osmemory.h"
#include"watchdog.h"
#include <stdio.h>

#ifdef _OS_DEBUG_ON_
#define _OS_EVENT_DEBUG_
#endif


//static OS_EVENT *OS_EVENTList[OS_EVENT_LIST_LENGTH];
static unsigned int OS_EVENTListCount;
OS_EVENT _os_event_list[OS_EVENT_LIST_LENGTH];

//static unsigned int OS_EVENTList_get_P;
//static unsigned int OS_EVENTList_set_P;
// OS_EVENT *OS_EVENTListHead;
// OS_EVENT *OS_EVENTListEnd;

void OS_EVENTInit()
{
    int i;
    //for (i = 0;i<=OS_EVENT_LIST_LENGTH;i++)
    //{
    //   OS_EVENTList[i] = 0;
    //}
    OS_EVENTListCount = 0;
    //OS_EVENTList_get_P = 0;
    //OS_EVENTList_set_P = 0;
    // OS_EVENTListHead = 0;
    // OS_EVENTListEnd = 0;
}


//return success or fail
OS_EVENT* sendEvent(unsigned int eventType,unsigned int shortMsg,unsigned char broadcast,void *data,unsigned int len)
{
    OS_EVENT *event;
    // event = _crateEvent(source,des,eventType,shortMsg,broadcast);
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

//     if (next_t)
//     {
// #ifdef _OS_DEBUG_ON_
//         printf("----OS the second event(type): %u \n",next_t->eventType);
// #endif
//         OS_EVENTListHead = next_t;
//     }
//     else
//     {
// #ifdef _OS_DEBUG_ON_
//         printf("----OS after head no event \n");
// #endif
//         OS_EVENTListHead = 0;
//     }
//    OS_EVENTListCount--;
    return e;
}

// //return success or fail
// unsigned char sendEventWithMsg(OS_TASK *source,OS_TASK *des,unsigned int eventType,unsigned int shortMsg,unsigned char broadcast,void *data,unsigned int len)
// {
//     OS_EVENT *event;
//     OS_MESSAGE *msg;
//     event = _crateEvent(source,des,eventType,shortMsg,broadcast);
//     if (!event)
//     {
//         return 0;
//     }
//     msg = createMsg(data,len);
//     if (!msg)
//     {
//         osMemRelease(event);
//         return 0;
//     }
//     if (event && msg)
//     {
//         event->msg_flag = 1;
//         event->msg = msg;
//         if (_addEventToList(event))
//         {
//             printf("------OS event add one\n");
// #ifdef _OS_LOG_ENABLE_
//     sysLog("--OS event add one\n");
// #endif
//             OS_EVENTListCount++;
//             return 1;
//         }
//     }

//     return 0;
// }


// OS_EVENT *_crateEvent(OS_TASK *source,OS_TASK *des,unsigned int eventType,unsigned int shortMsg,unsigned char broadcast)
// {
//     OS_EVENT *event;
//     if (OS_EVENTListCount >= OS_EVENT_LIST_LENGTH)
//     {
//         return 0;
//     }
//     event = (OS_EVENT *)osMalloc(sizeof(OS_EVENT));
//     if (event)
//     {
//         event->event_des_task = des;
//         event->event_source_task = source;
//         event->eventType = eventType;
//         event->event_short_inf = shortMsg;
//         event->msg_flag = 0;
//         event->broadcast = broadcast;
//         event->next = 0;
//     }

//     return event;
// }

// // release memory of event
// void releaseEvent(OS_EVENT *event)
// {
//     if (event->msg_flag)
//     {
//         releaseMsg(event->msg);
//     }
//     osMemRelease(event);
// }



