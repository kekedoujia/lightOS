#ifndef OSLOG_H
#define	OSLOG_H

#include "lightOS.h"
#include "os_config.h"

#ifdef	__cplusplus
extern "C" {
#endif

typedef void (*Log_Callback_Type)(char *);

void setLightOS_LogCallback(Log_Callback_Type cb); 
void sysLog(char *data);

#ifdef	__cplusplus
}
#endif



#endif	/* OSLOG_H */

