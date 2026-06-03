#include "osmemory.h"

#include <stdlib.h>

void *os_malloc(unsigned int length) { return calloc(length, 1); }

void os_free(void *ptr) { free(ptr); }
