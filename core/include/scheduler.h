#pragma once

#include <stdint.h>

#ifndef _IACOS_INTERNAL
#error "this can only be included from the OS"
#endif

#include <thread.h>


typedef struct scheduler {
        thread_t * head;
        thread_t * current;

}scheduler_t;



void scheduler_reschedule(scheduler_t * sched);