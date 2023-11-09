
#define _IACOS_INTERNAL

#include <thread.h>
#include <port.h>

void thread_create(	thread_t * thd,
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

void thread_start(thread_t * thd) {
	thd->state = OS_READY;
	//reschedule from interrupt ?????
}


void thread_set_delay(thread_t * thd, thread_t ** s_head, port_systick_t deadline) {
	port_enter_critical();
	thread_t * next = *s_head;
	*s_head = thd;
	thd->s_next = next;
	thd->delay.deadline = deadline;
	thd->state = OS_SUSPENDED;
	port_switch();
	port_exit_critical();
	
}

// void thread_yield(thread_t thd) {
// 	For this we need round robin scheduling
// }


void thread_eval_all(thread_t ** s_head, port_systick_t tick) {
	thread_t ** node;
	for( node = s_head; (*node) != NULL; node = &((*node)->next)) {
		if((*node)->delay.deadline <= tick) {
			(*node)->state = OS_READY;
			//remove element from list
			*node = (*node)->s_next;
			return;
		}
	} 
}




