#ifndef LIGHTOS_OSLOG_H_
#define LIGHTOS_OSLOG_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*LogCallback)(char *log);

void os_log_set_callback(LogCallback callback);
void os_log(char *log);

#ifdef __cplusplus
}
#endif

#endif  // LIGHTOS_OSLOG_H_
