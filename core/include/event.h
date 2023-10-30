#pragma once

#include <stdint.h>

#ifndef _IACOS_INTERNAL
#error "this can only be included from the OS"
#endif



typedef enum event_state {
        OS_TAKEN,
        OS_FREE
}event_state_t;

struct event {
	event_state_t state;
};



