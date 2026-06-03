# lightOS

lightOS is a small cooperative task manager for embedded projects. Users register periodic tasks, and the OS polling loop runs each task when its interval expires. Tasks can also publish events, and registered event handlers can receive those messages after the task loop.

The demo configuration targets Arduino, but the core code is plain C and can be adapted to other microcontroller platforms.

## Project Layout

```text
lightOS/
  lightOS/                     Core OS modules
    lightOS.c/.h               Setup and run loop
    task.c/.h                  Cooperative task scheduler
    event.c/.h                 Fixed-size event queue
    handle.c/.h                Event handler registry and dispatcher
    os_timer.c/.h              System time abstraction
    os_config.h                Compile-time configuration
    osmemory.c/.h              Memory wrappers
    oslog.c/.h                 Optional logging callback
    watchdog.c/.h              Watchdog hooks
    systypedef.h               OS structs
  libraries/                   Example libraries built on lightOS
    LEDs/
      LEDsPlatform.h           LED platform adapter interface
    ButtonMonitor/
      ButtonMonitorPlatform.h  Button platform adapter interface
    UdpServerConnection/
      UdpServerConnectionPlatform.h
```

## Configure The Platform

Configuration lives in `lightOS/os_config.h`.

For Arduino builds, keep:

```c
#define _Arduino_Platform_Application_
```

With this enabled, lightOS uses Arduino `millis()` through `os_get_time()`.

For non-Arduino platforms, disable `_Arduino_Platform_Application_`, provide a periodic timer interrupt, and call:

```c
_system_time_auto_plus();
```

from that interrupt. The timer unit should match the time constants in `os_config.h`.

Important capacity settings:

```c
#define OS_TASK_LIST_LENGTH     10
#define OS_EVENT_LIST_LENGTH    5
#define OS_HANDLER_LIST_LENGTH  5
```

Increase these if your application registers more tasks, queued events, or handlers. Larger values use more static RAM.

## Basic Usage

Include the OS header:

```c
#include "lightOS.h"
```

Initialize once:

```c
os_setup();
```

Run continuously.

On Arduino:

```c
void loop()
{
    os_run_non_blocking();
}
```

On a bare-metal C target:

```c
int main(void)
{
    os_setup();
    os_run();
    return 0;
}
```

`os_run()` is a blocking run loop for platforms where the application can own a `while (1)` loop. For Arduino-style frameworks, call one non-blocking iteration from the framework loop:

```c
os_run_non_blocking();
```

## Tasks

A task callback has this shape:

```c
unsigned int my_task(int opt)
{
    /* do a short piece of work */
    return 1;
}
```

Register it with:

```c
OsTask *task = task_register(my_task, OS_ST_PER_SECOND, TASK_RUN, 0);
```

Arguments:

- `task_callback`: task callback.
- `interval`: normal task interval.
- `status`: `TASK_RUN` or `TASK_IDLE`.
- `temp_interval`: first temporary delay. Pass `0` to run as soon as possible, or `-1` to use the normal interval immediately.

Useful task APIs:

```c
task_pause(task);
task_restart(task);
task_next_duty_delay(task, OS_ST_PER_100_MS);
self_next_duty_delay(OS_ST_PER_SECOND);
OsTask *self = task_self_handler();
```

Tasks should return quickly. lightOS is cooperative, so a long-running task blocks all other tasks and event handlers.

## Events And Handlers

Register a handler:

```c
void on_event(OsEvent *event)
{
    /* event->event_type, event->event_short_inf, event->msg, event->msg_len */
}

OsEventHandler *handler =
    os_event_handler_register(on_event, APP_EVENT_TYPE | 1, 1);
```

Send an event:

```c
int payload = 123;
os_event_send(APP_EVENT_TYPE | 1, 0, 0, &payload, sizeof(payload));
```

Event behavior:

- Events are queued in FIFO order.
- `os_event_send()` copies the payload into OS-managed memory.
- The payload is released after the event has been dispatched.
- If `broadcast` is `0`, only the first matching enabled handler runs.
- If `broadcast` is greater than `0`, every matching enabled handler runs.
- `os_event_send()` returns `NULL` if the event queue is full or payload allocation fails.

## Example Libraries

`libraries/LEDs` registers a task to blink and control LEDs independently.

`libraries/ButtonMonitor` registers a task to poll buttons and report short or long press callbacks.

`libraries/UdpServerConnection` registers a UDP listening task and wraps simple send/receive helpers for Arduino Ethernet-style projects.

These libraries are examples of how to build application modules on top of `task_register()`.

Each example library has two layers:

- The library layer contains platform-independent logic.
- The platform layer contains hardware or framework calls.

For a new platform, keep the main library files and provide implementations for the matching platform interface:

```text
libraries/LEDs/LEDsPlatform.h
libraries/ButtonMonitor/ButtonMonitorPlatform.h
libraries/UdpServerConnection/UdpServerConnectionPlatform.h
```

The Arduino implementations are provided as defaults:

```text
libraries/LEDs/LEDsArduinoPlatform.cpp
libraries/ButtonMonitor/ButtonMonitorArduinoPlatform.cpp
libraries/UdpServerConnection/UdpServerConnectionArduinoPlatform.cpp
```

When porting to another platform, replace those default platform `.cpp` files or exclude them from your build and add your own implementation files with the same platform function names.

## Notes

- `os_setup()` initializes tasks, events, and event handlers.
- Timer wraparound is handled through unsigned time subtraction.
- The scheduler uses fixed-size static arrays, so capacity limits are compile-time settings.
- The core has no preemption. Shared data touched by interrupts still needs normal embedded synchronization care.
