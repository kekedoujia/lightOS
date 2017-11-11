#include "lightOS.h"
//#include "handle.h"
//#include "event.h"
//#include "task.h"
//#include "watchdog.h"

void osSetup()
{
    // init system timer
    #ifndef LIGHT_OS_USING_EXTERNAL_TIMER
    osTimerInit();
    #endif
    // init event handler
    //OS_EVENTHandlerInit();

#ifdef _WATCH_DOG_ENABLE_
    // init watch dog
    watchDogInit();
#endif
    // init task
    taskInit();
}

void osRun()
{
#ifndef _Arduino_Platform_Application_
    while(1)
    {
#endif
        // run each task
        os_taskProcessing();
        os_eventHandlerProcess();

#ifdef _WATCH_DOG_ENABLE_
        watchDogFeed();
#endif
        // working on each event
        //OS_EVENTHandlerProcess();
#ifndef _Arduino_Platform_Application_
    }
#endif
}


void osRunNoneBlock()
{
    // run each task
    os_taskProcessing();
    // working on each event
    OS_EVENTHandlerProcess();
}
