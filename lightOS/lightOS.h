#ifndef LIGHTOS_H
#define	LIGHTOS_H

#include "systypedef.h"
#include "os_config.h"
#include "osmemory.h"
#include "handle.h"
#include "event.h"
#include "task.h"
#include "watchdog.h"
#include "os_timer.h"
#include "oslog.h"


#ifdef	__cplusplus
extern "C" {
#endif

void osSetup(void);
void osRun(void);

#ifdef	__cplusplus
}
#endif

#endif	/* LIGHTOS_H */

