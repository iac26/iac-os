/* 
	(c) 2023 - Iacopo Sprenger

	Startup for cortex-m0+


*/



/*
	DEFINITIONS
 */

#define CONTROL_MODE_PRIVILEGED             0
#define CONTROL_MODE_UNPRIVILEGED           1
#define CONTROL_USE_MSP                     0
#define CONTROL_USE_PSP                     2

#define SCB_VTOR                            0xE000ED08



/*
	Control register init value
	privileged mode and PSP enabled
 */
 #define CONTROL_INIT	(CONTROL_USE_PSP |		\
			CONTROL_MODE_PRIVILEGED)



	.syntax unified
	.cpu cortex-m0plus
	.fpu softvfp
	.thumb


	.text

/*
	Entry point
 */

	.align	2
	.thumb_func
	.global	_crt0_entry

_crt0_entry:
	cpsid	i

	/* init main stack */
	ldr	r0, =__main_stack_end__
	msr	MSP, r0

	/* init process stack */
	ldr	r0, =__process_stack_end__
	msr	PSP, r0
	
	/* init cpu mode */
	movs	r0, #CONTROL_INIT
	msr	CONTROL, r0
	isb

	/* initialize cpu core */
	bl 	__cpu_init

	/* call early init */
	bl 	__early_init

	/* fill main stack */

	/* random data in stacks */

	/* fill process stack */

	/* random data in stacks */

	/* init vectors */

	/* we keep them as they are for now */

	/* init data */

	ldr	r1, =__textdata_base__
	ldr	r2, =__data_base__
	ldr	r3, =__data_end__
dloop:
	cmp 	r2, r3
	bge 	enddloop
	ldr	r0, [r1]
	str 	r0, [r2]
	adds	r1, #4
	adds	r2, #4
	b 	dloop
enddloop:

	/* init bss */

	movs	r0, #0
	ldr	r1, =__bss_base__
	ldr	r2, =__bss_end__
bloop:
	cmp 	r1, r2
	bge 	endbloop
	str 	r0, [r1]
	adds	r1, #4
	b 	bloop
endbloop:

	/* call late init */
	bl 	__late_init


	/* init ram areas  */

	/*TODO: Figure out what this does */


	/* call constructors */
	/* not sure if this is needed ?? */


	/* start main program */
	bl 	main

	/* call destructors */
	/* not sure if this is needed ?? */

	/* branch to exit handler*/
	ldr     r1, =__default_exit
	bx      r1


