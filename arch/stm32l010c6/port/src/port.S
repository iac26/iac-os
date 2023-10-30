
/* Portability functions defined in assembly */

	.syntax unified
	.cpu cortex-m0plus
	.fpu softvfp
	.thumb


	.text



	/* a context switch can be requested by calling the PendSV handler */
PendSV_Handler:
	/* Save the context*/
	mrs	r0, psp		
	subs	r0, r0, #32	
	str	r0, []	
	stmia	r0!, {r4-r7}	
	mov	r4, r8		
	mov	r5, r9		
	mov	r6, r10		
	mov	r7, r11		
	stmia	r0!, {r4-r7}	



