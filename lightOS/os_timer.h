#ifndef OS_TIMER_H
#define	OS_TIMER_H

#include "lightOS.h"
#include "limits.h"
#include "stdint.h"


#ifdef	__cplusplus
extern "C" {
#endif
	
#define MAX_OS_TIMER_COUNT ULONG_MAX //4294967295L  //unsigned long


#ifndef LIGHT_OS_USING_EXTERNAL_TIMER
void osTimerInit(void);
void _system_time_auto_plus(void);
#endif

unsigned long getSysTime(void);
void progDelay(unsigned long ts);

#ifdef	__cplusplus
}
#endif

#endif	/* TIMER_H */

