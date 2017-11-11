#include "lightOS.h"
#include <stdio.h>


Log_Callback_Type _lightOS_log_callback_;

void setLightOS_LogCallback(Log_Callback_Type cb){
      _lightOS_log_callback_ = cb;
}

void sysLog(char *log)
{
#ifdef _OS_LOG_ENABLE_
	_lightOS_log_callback_(log);
#endif
}