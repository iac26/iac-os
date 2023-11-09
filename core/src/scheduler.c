
#define _IACOS_INTERNAL

#include <port.h>

#include <thread.h>
#include <scheduler.h>

// the scheduler needs to keep track of the list of tasks


/**
 *  Add thread in the sorted linked list of threads
 **/ 
void scheduler_add_thread(	scheduler_t * sch,
				thread_t * thd) {
	thread_t ** node;
	//insert thread in list such that they are sorted by priority
	port_enter_critical();
	for( node = &(sch->head); (*node) != NULL; node = &((*node)->next)) {
		if((*node)->priority < thd->priority) {
			thd->next = (*node);
			(*node) = thd;
			port_exit_critical();
			return;
		}
	} 
	//case where the thread is last
	iacos_panic("no idle thread");
}


/*
* Very simplest scheduler where we just choose the highest priority thread that is ready
*/
void scheduler_reschedule(scheduler_t * sch) {
	thread_t * node;
	for( node = sch->head; node != NULL; node = node->next) {
		if(node->state == OS_READY) {
			sch->cur = node;
		}
	}
	//this should return the idle thread
	iacos_panic("idle thread not ready!");
}

