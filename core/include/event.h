#pragma once

#include <stdint.h>
#include <stddef.h>

#include <iacos.h>


// DEFINE A PROPER WAY TO KNOW WHAT IS ALLOWED TO BE INCLUDED
// #ifndef _IACOS_INTERNAL
// #error "this can only be included from the OS"
// #endif



/**
 * How can the event mechanism be used ?
 * 
 * the event is initially detached from any thread
 * 
 * The event can be held by a thread. 
 * Only one thread can own an event. 
 * The thread can release the event, thus detaching it. 
 * 
 * When a thread tries to take an owned event, it is placed in the event's waiting list. 
 * When an event is released, the highest priority waiting thread is marked as ready. 
 * 
 * when an unowned event is released, all waiting threads are marked as ready
 * 
 * -- Four functions to interact with events --
 * 
 * These functions treat the event as some kind of mutex
 * 
 * This function will attempt to own the event if it is free
 * evt_take()
 * if the event is free, own the event.
 * if the event is owned, put the thread in the waiting list according to its priority.
 * 
 * evt_release()
 * if the thread owns the event, release it and mark the highest priority thread as ready.
 * if the thread does not own the event -> panic handler.
 * 
 * 
 * These functions treat the event as a semaphore
 * 
 * evt_wait()
 * put the thread in the event's waiting list
 * 
 * evt_signal()
 * release all waiting threads
 * 
 * 
 * 
 * 
 * 
 **/


typedef enum event_state {
        OS_TAKEN,
        OS_FREE
}event_state_t;

struct event {
	event_state_t state;
        thread_t * waiting;
        thread_t * owner;
};

void evt_take(event_t * evt);
void evt_release(event_t * evt);

void evt_wait(event_t * evt);
void evt_signal(event_t * evt);

