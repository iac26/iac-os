#pragma once

#include <stdint.h>

#ifndef _IACOS_INTERNAL
#error "this can only be included from the OS"
#endif

#include <iacos.h>

#include <port.h>

#include <event.h>





typedef enum thread_state {
	OS_RUNNING,	//Thread is currently running
	OS_READY,	//Thread is ready to run
	OS_SUSPENDED,	//Thread is suspended (waiting on scheduled time)
	OS_WAITING,	//Thread is waiting for an event
	OS_DISABLED	//Thread is disabled
}thread_state_t;


struct delay {
        port_systick_t deadline;     //time at which the delay expires
};


struct thread {
	thread_t * next; //global thread list next
	thread_t * prev; //global thread list prev
	thread_t * s_next; //suspended thread list next
	thread_prio_t priority;
	port_context_t context;
	thread_state_t state;
	delay_t delay;
	event_t * pending;
};




void thread_create(	thread_t * thd,
			thread_prio_t prio, 
			void (*entry)(void), 
			uint32_t * stack, 
			uint32_t stack_size);


void thread_createI(	thread_t * thd,
			thread_prio_t prio, 
			void (*entry)(void), 
			uint32_t * stack, 
			uint32_t stack_size);



void thread_eval_all(thread_t ** head, port_systick_t tick);