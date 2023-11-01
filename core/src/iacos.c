
#define _IACOS_INTERNAL

#include <port.h>
#include <scheduler.h>
#include <thread.h>
#include <iacos.h>


extern port_context_t port_current_context;


struct {
	scheduler_t sch;

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
__attribute__((naked)) void iacos_reschedule(void) {

	iacos.sch.cur->context = port_current_context;
	
	scheduler_reschedule(&iacos.sch);

	port_current_context = iacos.sch.cur->context;
}


__attribute__((naked)) void iacos_systick(void) {
	//perform systick stuff
}
