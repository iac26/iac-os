
#define _IACOS_INTERNAL

#include <thread.h>
#include <port.h>

void thread_createI(	thread_t * thd,
			thread_prio_t prio, 
			void (*entry)(void), 
			uint32_t * stack, 
			uint32_t stack_size) {

	thd->priority = prio;
	thd->state = OS_DISABLED;
	thd->next = NULL;
	uint32_t * stack_end = stack + stack_size;
	port_context_init(&(thd->context), stack_end, entry);
}

void thread_create(	thread_t * thd,
			thread_prio_t prio, 
			void (*entry)(void), 
			uint32_t * stack, 
			uint32_t stack_size) {
	port_enter_critical();
	thread_createI(thd, prio, entry, stack, stack_size);
	port_exit_critical();
}

void thread_startI(thread_t * thd) {
	thd->state = OS_READY;
	//reschedule from interrupt ?????
}

void thread_start(thread_t * thd) {
	port_enter_critical();
	thread_startI(thd);
	//rescedule definetely
	port_exit_critical();
}




