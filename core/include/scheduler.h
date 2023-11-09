#pragma once

#include <stdint.h>
#include <stddef.h>

#ifndef _IACOS_INTERNAL
#error "this can only be included from the OS"
#endif

#include <thread.h>


typedef struct scheduler {
        thread_t * head;
        thread_t * cur;

}scheduler_t;


void scheduler_add_thread(	scheduler_t * sch,
				thread_t * thd);

void scheduler_reschedule(scheduler_t * sch);