#pragma once

#include <stdint.h>

#ifndef _IACOS_INTERNAL
#error "this can only be included from the OS"
#endif


#include <thread.h>


void iacos_reschedule(void);

thread_t * iacos_get_current_thd(void);
