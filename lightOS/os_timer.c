#include "lightOS.h"

#ifndef LIGHT_OS_USING_EXTERNAL_TIMER

unsigned long os_system_time;

void osTimerInit(void)
{
   os_system_time = 0;
}


unsigned long getSysTime(void)
{
    return os_system_time;
		//return HAL_GetTick();
}


// should be used in time int every 1ms.
void _system_time_auto_plus(void)
{
    os_system_time++;
}
#endif

#ifdef _Arduino_Platform_Application_
#include "Arduino.h"

#ifdef  __cplusplus
extern "C" {
#endif
unsigned long getSysTime(void)
{
    return millis();
}
#ifdef  __cplusplus
}
#endif

#endif


void progDelay(unsigned long ts){
	unsigned long start = getSysTime();
	while (getSysTime() - start < ts){;}
}

