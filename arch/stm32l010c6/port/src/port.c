

#define _IACOS_INTERNAL

#include <port.h>


#include <internal.h>



/**
 * What does the stack look like after a context switch
 *
        Top of the Stack (Higher Address)
+------+
| xPSR |
+------+
|  PC  |
+------+
|  LR  |
+------+
| R12  |
+------+
|  R3  |
+------+
|  R2  |
+------+
|  R1  |
+------+
|  R0  | <-- PSP
+------+    
        Bottom of the Stack (Lower Address)
 * 
 * 
 **/


port_context_t port_current_context;



void port_context_init(port_context_t * ctx, uint32_t * stack_end, void(*task_func)(void)) {
	uint32_t * stack_pointer = stack_end;
	*stack_pointer = PORT_xPSR_INIT;	/* xPSR */
	stack_pointer -= sizeof(uint32_t);			
	*stack_pointer = (uint32_t)task_func;	/* PC */
	stack_pointer -= sizeof(uint32_t);
	*stack_pointer = 0xFFFFFFFF;		/* LR */
	stack_pointer -= sizeof(uint32_t);
	for(uint8_t i = 0; i < 12; i++) {
		*stack_pointer = 0;		/* Registers */
		stack_pointer -= sizeof(uint32_t);
	}
	*stack_pointer = 0; /* R4 */
	ctx->psp = stack_pointer;
}



