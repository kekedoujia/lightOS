
#ifndef OS_CONFIG_H
#define	OS_CONFIG_H

// system function shift
//#define _WATCH_DOG_ENABLE_  1
//#define _OS_LOG_ENABLE_     1
#define LIGHT_OS_USING_EXTERNAL_TIMER     1
#define LIGHT_OS_MINIMUM_TIME_UNIT_1_MS
//#define _OS_DEBUG_ON_


#ifndef LIGHT_OS_MINIMUM_TIME_UNIT_1_MS

#define LIGHT_OS_MINIMUM_TIME_UNIT_5_MS 
#define	OS_ST_PER_5_MS    1L

#else

#define OS_ST_PER_1_MS		1L
#define OS_ST_PER_5_MS      5L

#endif

// timer

#define OS_ST_PER_10_MS    OS_ST_PER_5_MS*2L
#define OS_ST_PER_20_MS    OS_ST_PER_10_MS*2L
#define OS_ST_PER_50_MS    OS_ST_PER_10_MS*5L
#define OS_ST_PER_100_MS    OS_ST_PER_10_MS*10L
#define OS_ST_PER_SECOND   OS_ST_PER_100_MS*10L
#define OS_ST_PER_MINUTE   OS_ST_PER_SECOND*60L
#define OS_ST_PER_30_MINUTE   OS_ST_PER_MINUTE*30L

// system config
#ifndef OS_TASK_LIST_LENGTH
#define OS_TASK_LIST_LENGTH 10
#endif // !OS_TASK_LIST_LENGTH

#ifndef OS_EVENT_LIST_LENGTH
#define OS_EVENT_LIST_LENGTH 5
#endif // !OS_EVENT_LIST_LENGTH

#ifndef OS_HANDLER_LIST_LENGTH
#define OS_HANDLER_LIST_LENGTH  5
#endif // !OS_HANDLER_LIST_LENGTH

// OS event
#define OS_EVT_SYSTEM_INIT  1

#endif	/* OS_CONFIG_H */

