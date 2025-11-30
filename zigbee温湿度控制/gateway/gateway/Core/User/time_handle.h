#ifndef __TIME_HANDLE_H__
#define __TIME_HANDLE_H__

#include "tim.h"

typedef struct Timer {
    unsigned int timeout;
    unsigned int repeat;
    void (*timeout_cb)(void);
    struct Timer* next;
}Timer;

void timer_peripheral_init(void);
void timer_init(struct Timer* handle, void(*timeout_cb)(), unsigned int timeout, unsigned int repeat);
int  timer_start(struct Timer* handle);
void timer_stop(struct Timer* handle);
void timer_ticks(void);
void timer_loop(void);

#endif


/*
*************************************
软定时使用:

*************************************
*/
