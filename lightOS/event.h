
#ifndef OS_EVENT_H
#define	OS_EVENT_H

#include "os_config.h"
#include "lightOS.h"

#define OS_EVENT_TYPE  0x0000
#define APP_EVENT_TYPE 0x4000
#define EVENT_BROAD_CAST_BIT  0x2000

#ifdef	__cplusplus
extern "C" {
#endif

void OS_EVENTInit(void);
OS_EVENT *sendEvent(unsigned int eventType,unsigned int shortMsg,unsigned char broadcast,void *data,unsigned int len);
//unsigned char sendEventWithMsg(OS_TASK *source,OS_TASK *des,unsigned int eventType,unsigned int shortMsg,unsigned char broadcast,void *data,unsigned int len);
//OS_EVENT *_crateEvent(OS_TASK *source,OS_TASK *des,unsigned int eventType,unsigned int shortMsg,unsigned char broadcast);
//void releaseEvent(OS_EVENT *event);
OS_EVENT *getEventFromList(void);


#ifdef	__cplusplus
}
#endif

#endif	/* ENENT_H */

