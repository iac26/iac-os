#pragma once

#include <stdint.h>




/******************************
 * SVC NUMBERS
 ******************************/



/******************************
 * THREADS
 ******************************/

typedef struct thread thread_t;

typedef uint8_t thread_prio_t;


/******************************
 * DELAY
 ******************************/

typedef struct delay delay_t;


/******************************
 * EVENT
 ******************************/

typedef struct event event_t;


void iacos_init(void);
void iacos_start(void);
void iacos_panic(const char * msg);