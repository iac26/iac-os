#include <event.h>


#define _IACOS_INTERNAL
#include <thread.h>
#include <internal.h>




void evt_insert_thd(event_t * evt, thread_t * thd) {
	thread_t ** node;
	port_enter_critical();
	for( node = &(evt->waiting); (*node) != NULL; node = &((*node)->w_next)) {
		if((*node)->priority < thd->priority) {
			thd->state = OS_WAITING;
			thd->w_next = (*node);
			(*node) = thd;
			port_switch();
			port_exit_critical();
			return;
		}
	} //thread has lowest priority or list is empty
	(*node) = thd;
	(*node)->w_next = NULL;
	(*node)->state = OS_WAITING;
}

void evt_remove_first(event_t * evt) {
	thread_t ** node = &(evt->waiting);
	if(*node != NULL) {
		(*node)->state = OS_READY;
		(*node) = (*node)->w_next;
	}
}

void evt_remove_all(event_t * evt) {
	thread_t ** node = &(evt->waiting);
	thread_t ** tmp;
	for( node = &(evt->waiting); (*node) != NULL; node = tmp) {
		(*node)->state = OS_READY;
		tmp = &((*node)->w_next);
		*node = NULL;
	} 
}

/*
* When the event is free
*/
void evt_take(event_t * evt) {
	if(evt->owner = NULL) { //if the event is free, take it
		evt->owner = iacos_get_current_thd();
		//no need to switch here
	} else {
		port_enter_critical();
		evt_insert_thd(evt, iacos_get_current_thd());
		//also swtches context
		port_switch();
		port_exit_critical();

		//once we comeback here, take the event
		evt->owner = iacos_get_current_thd();
		
	}
}

void evt_release(event_t * evt) {
	port_enter_critical();
	if(evt->owner == iacos_get_current_thd()) {
		evt->owner = NULL;
		evt_remove_first(evt);
		port_switch();
		port_exit_critical();
	} else {
		iacos_panic("released un-owned evt");
	}
}

void evt_wait(event_t * evt) {
	port_enter_critical();
	evt_insert_thd(evt, iacos_get_current_thd());
	port_switch();
	port_exit_critical();
}

void evt_signal(event_t * evt) {
	port_enter_critical();
	evt_remove_all(evt);
	port_switch();
	port_exit_critical();
}