
/* Portability functions defined in assembly */

	.syntax unified
	.cpu cortex-m0plus
	.fpu softvfp
	.thumb


	.extern port_current_context

	.text
	.global iacos_reschedule
	.global iacos_systick

	
.thumb_func
	/* a context switch can be requested by calling the PendSV handler */
	/* So whenever we want to request a reschedule, we trigger pendSV  */
PendSV_Handler:
	/* Save the context*/
	cpsid	i
	mrs	r0, psp		
	subs	r0, r0, #32
	ldr	r1, =port_current_context
	str	r0, [r1]
	stmia	r0!, {r4-r7}	
	mov	r4, r8		
	mov	r5, r9		
	mov	r6, r10		
	mov	r7, r11		
	stmia	r0!, {r4-r7}
	bl 	iacos_reschedule
	/* Restore the context */
	ldr	r0, =port_current_context 
	adds	r0, r0, #16	
	ldmia	r0!, {r4-r7}	
	mov	r8, r4		
	mov	r9, r5		
	mov	r10, r6		
	mov	r11, r7		
	subs	r0, r0, #32	
	ldmia	r0!, {r4-r7}	
	adds	r0, r0, #32	
	msr	psp, r0     
	cpsie	i  
	bx	lr

.thumb_func

SysTick_Handler:
	/* Save the context*/
	cpsid	i
	mrs	r0, psp		
	subs	r0, r0, #32
	ldr	r1, =port_current_context
	str	r0, [r1]
	stmia	r0!, {r4-r7}	
	mov	r4, r8		
	mov	r5, r9		
	mov	r6, r10		
	mov	r7, r11		
	stmia	r0!, {r4-r7}
	bl 	iacos_systick
	bl 	iacos_reschedule
	/* Restore the context */
	ldr	r0, =port_current_context 
	adds	r0, r0, #16	
	ldmia	r0!, {r4-r7}	
	mov	r8, r4		
	mov	r9, r5		
	mov	r10, r6		
	mov	r11, r7		
	subs	r0, r0, #32	
	ldmia	r0!, {r4-r7}	
	adds	r0, r0, #32	
	msr	psp, r0      
	cpsie	i  
	bx	lr

