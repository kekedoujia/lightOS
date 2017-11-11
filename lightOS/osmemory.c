#include<stdlib.h>
#include "os_config.h"
#include"osmemory.h"


void *osMalloc(unsigned int l)
{
    return calloc(l,1);
}

void osMemRelease(void *p)
{
    free(p);
}
