
#define _IACOS_INTERNAL

#include <port.h>
#include <scheduler.h>
#include <thread.h>
#include <iacos.h>


extern port_context_t port_current_context;


struct {
	scheduler_t sch;
	thread_t * s_head;
	port_systick_t tick;
} iacos;




/*
 PUBLIC FUNCTIONS
*/
void iacos_init(void) {

}


void iacos_start(void) {
	
}



void iacos_panic(const char * msg) {
	//report error

	//stack trace

	for(;;) {
		//loop forever
		//or recover 
	}
}





/*
 PRIVATE FUNCTIONS
*/

//called from PendSV context
//should arrive here with interrupts disabled
__attribute__((naked)) void iacos_reschedule(void) {

	iacos.sch.cur->context = port_current_context;
	
	scheduler_reschedule(&iacos.sch);

	port_current_context = iacos.sch.cur->context;
}


//should arrive here with interrupts disabled
__attribute__((naked)) void iacos_systick(void) {

	iacos.sch.cur->context = port_current_context;

	// increment systick counter
	iacos.tick += 1;

	//compute delays
	thread_eval_all(&(iacos.s_head), iacos.tick);

	scheduler_reschedule(&iacos.sch);

	port_current_context = iacos.sch.cur->context;

}


thread_t * iacos_get_current_thd(void) {
	return iacos.sch.cur;
}