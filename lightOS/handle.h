#ifndef OS_HANDLER_H
#define	OS_HANDLER_H

#ifdef	__cplusplus
extern "C" {
#endif

#define MSG_TYPE_SUPPORT_LENGTH 3

#include "lightOS.h"



void OS_EVENTHandlerInit(void);
EVENT_HANDLER *eventHandlerRegister(void (*handlerFun)(OS_EVENT *e),unsigned int eventType,unsigned char status);
void eventHandlerEnable(unsigned int handlerNum);
void eventHandlerDisable(unsigned int handlerNum);
unsigned char eventHandlerStatus(unsigned int handlerNum);
void OS_EVENTHandlerProcess(void);


#ifdef	__cplusplus
}
#endif

#endif	/* HANDLE_H */

