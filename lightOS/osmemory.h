#ifndef LIGHTOS_OSMEMORY_H_
#define LIGHTOS_OSMEMORY_H_

#ifdef __cplusplus
extern "C" {
#endif

void *os_malloc(unsigned int length);
void os_free(void *ptr);

#ifdef __cplusplus
}
#endif

#endif  // LIGHTOS_OSMEMORY_H_
