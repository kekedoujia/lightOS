#include "os_config.h"
#include "watchdog.h"

char dogStatus;

void watchDogInit(void)
{
    dogStatus = 0;
}

void watchDogFeed(void)
{

}

void watchDogEnable(void)
{

    dogStatus = 1;
}

void watchDogStop(void)
{

    dogStatus = 0;
}

