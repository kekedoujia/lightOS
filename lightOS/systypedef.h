/*
 * IncFile1.h
 *
 * Created: 2014/11/8 4:13:56
 *  Author: JI
 */


#ifndef _OS_TYPEDEF_H_
#define _OS_TYPEDEF_H_

typedef struct _task{
	unsigned int task_num;
	unsigned char task_status;  //1:run 2:stop
	unsigned long last_run_time; //ms
	unsigned long interval_time; //ms
    long temp_interval_time;
	unsigned int (*taskP)(int opt);
} OS_TASK;

// typedef  struct _message{
// 	unsigned int msg_len;
// 	void *msg;
// } OS_MESSAGE;

typedef struct _event{
	unsigned int eventType;
	unsigned int event_short_inf;
	unsigned char broadcast_flag;
	void *msg;
	unsigned int msg_len;
} OS_EVENT;


typedef struct _handler{
	unsigned int handle_num;
	unsigned char handle_status;
	unsigned int eventType;
	void (*handleP)(OS_EVENT *e);
} EVENT_HANDLER;


#endif /* INCFILE1_H_ */
