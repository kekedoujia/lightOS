#ifndef OS_TIMER_H
#define	OS_TIMER_H

#include "os_config.h"
#include "limits.h"
#include "stdint.h"


unsigned long getSysTime(void);


#ifdef	__cplusplus
extern "C" {
#endif
	
#define MAX_OS_TIMER_COUNT ULONG_MAX //4294967295L  //unsigned long



#ifndef LIGHT_OS_USING_EXTERNAL_TIMER
void osTimerInit(void);

void _system_time_auto_plus(void);
#endif


void progDelay(unsigned long ts);

#ifdef	__cplusplus
}
#endif

#endif	/* TIMER_H */

