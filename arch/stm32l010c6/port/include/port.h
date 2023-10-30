#pragma once

#include <stdint.h>


/** *******************************************************
 * Context
 **********************************************************/
typedef struct port_context {
		uint32_t * psp;
} port_context_t;


extern port_context_t current_context;


/* Initial value for xPSR  -> check what should be placed here...*/
#define PORT_xPSR_INIT	0x00 

/**
 * After context save, we will have the following stack 
 * 
 * TOP (Higher address)
 * xPSR
 * PC
 * LR
 * R12
 * R3
 * R2
 * R1
 * R0   <-- PSP
 * R11
 * R10
 * R9
 * R8
 * R7
 * R6
 * R5
 * R4   <-- ctx->psp
 * BOTTOM
 **/

#define port_context_save(ctx)     \
	asm volatile (             \
		".syntax unified 	\n" 					\
		"mrs	r0, psp		\n" /* Load PSP into R0 */              \
		"subs	r0, r0, #32	\n" /* Prepare space on the stack */    \
		"str	r0, [%0]	\n" /* Store the new PSP value to ctx */\
		"stmia	r0!, {r4-r7}	\n" /* Store low registers */           \
		"mov	r4, r8		\n" /* Store high registers */          \
		"mov	r5, r9		\n" /* Store high registers */          \
		"mov	r6, r10		\n" /* Store high registers */          \
		"mov	r7, r11		\n" /* Store high registers */          \
		"stmia	r0!, {r4-r7}	\n" /* Store high registers */          \
		: : "r" ((ctx)->psp) : "r0"        /* ctx is input, R0 is modified */ \
	)

#define port_context_restore(ctx) \
	asm volatile  (            	 					\
		".syntax unified 	\n" 					\
		"ldr    r0, [%0]        \n" /* Load PSP value from ctx into R0*/\
		"adds	r0, r0, #16	\n" /* Fetch high registers location */ \
		"ldmia	r0!, {r4-r7}	\n" /* Read high registers */           \
		"mov	r8, r4		\n" /* Read high registers */           \
		"mov	r9, r5		\n" /* Read high registers */           \
		"mov	r10, r6		\n" /* Read high registers */           \
		"mov	r11, r7		\n" /* Read high registers */           \
		"subs	r0, r0, #32	\n" /* Fetch low registers location */  \
		"ldmia	r0!, {r4-r7}	\n" /* Read high registers */           \
		"adds	r0, r0, #32	\n" /* Fetch normal psp location */	\
		"msr    psp, r0         \n" /* Set the PSP */                   \
		: : "r" ((ctx)->psp) : "r0"      /* ctx is input, R0 is modified */  \
	)

static inline void port_context_init(port_context_t * ctx, uint32_t * stack_end, void(*task_func)(void)) {
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




	



/** *******************************************************
 * System Tick
 **********************************************************/
typedef uint32_t port_systick_t;










