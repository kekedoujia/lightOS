#include "lightOS.h"
//#include "handle.h"
//#include "event.h"
#include "task.h"
#include "watchdog.h"

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
    while(1)
    {
        // run each task
        os_taskProcessing();
        // working on each event
        //OS_EVENTHandlerProcess();
    }
}

void osRunNoneBlock()
{
    // run each task
    os_taskProcessing();
    // working on each event
    OS_EVENTHandlerProcess();
}
