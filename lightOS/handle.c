#include "os_config.h"
#include <stdio.h>
#include "lightOS.h"
#include "string.h"

static EVENT_HANDLER OS_EVENTHandlerList[OS_HANDLER_LIST_LENGTH];
static unsigned int OS_EVENTHandler_count = 0;

void OS_EVENTHandlerInit()
{
    int i;
    memset((char *)OS_EVENTHandlerList,0,sizeof(OS_EVENTHandlerList));
    OS_EVENTHandler_count = 0;
}

// pare eventType with function, return 1 success; 0 false;
EVENT_HANDLER *eventHandlerRegister(void (*handlerFun)(OS_EVENT *e),unsigned int eventType,unsigned char status)
{
    int i;
    EVENT_HANDLER * handler;
    // check if exesit
    //unsigned char ex = 0;
    // handler = &OS_EVENTHandlerList[OS_EVENTHandler_count];
    for (i = 0;i<OS_EVENTHandler_count;i++)
    {
        handler = &(OS_EVENTHandlerList[i]);
        if (handler->handleP == handlerFun && handler->eventType == eventType)
        {
            return handler;
        }
    }
    // if event handler not exist
    handler = &(OS_EVENTHandlerList[OS_EVENTHandler_count++]);
    // add function
    handler->handleP = handlerFun;
    // add handle event type
    handler->eventType = eventType;
    //_eventHandler_addEventType(handler,eventType);
    //add to list
    handler->handle_status = status;
    return handler;
}


void eventHandlerEnable(unsigned int handlerNum)
{
    OS_EVENTHandlerList[handlerNum].handle_status = 1;
}

void eventHandlerDisable(unsigned int handlerNum)
{
    OS_EVENTHandlerList[handlerNum].handle_status = 0;
}

unsigned char eventHandlerStatus(unsigned int handlerNum)
{
    return OS_EVENTHandlerList[handlerNum].handle_status;
}

void OS_EVENTHandlerProcess()
{
    int i;
#ifdef _OS_LOG_ENABLE_
    char log[100];
#endif
    OS_EVENT *event;
    EVENT_HANDLER *handler;


    event = getEventFromList();
    while(event != NULL)
    {
#ifdef _OS_DEBUG_ON_
        printf("----OS  get a event %u\n",event->eventType);
#endif
        for (i=0;i<OS_EVENTHandler_count;i++)
        {
                handler = &OS_EVENTHandlerList[i];
                if (handler->handle_status == 1 && handler->eventType == event->eventType)  // handler enable and find the right handler
                {
#ifdef _OS_DEBUG_ON_
                    printf("Call event handler: %d    Event type: %d\n---------------------\n",handler->handle_num,event->eventType);
#endif
#ifdef _OS_LOG_ENABLE_
                    sprintf(log,"Call event handler: %d    Event type: %d\n---------------------\n",handler->handle_num,event->eventType);
                    sysLog(log);
#endif
                    //run the handler function
                    handler->handleP(event);

#ifdef _WATCH_DOG_ENABLE_
                    watchDogFeed();
#endif

                    if (event->broadcast_flag <= 0)
                    {
                        break;
                    }
                }
        }
        event = getEventFromList();
    }
}

