/*
    (c) 2023 Iacopo Sprenger



 */



	.syntax unified
	.cpu    cortex-m0

	.section isr_vectors
	.align 	4

	.long	__main_stack_end__
	.long	Reset_Handler
	.long 	NMI_Handler
	.long	HardFault_Handler
	.long 	Vector4
	.long 	Vector5
	.long 	Vector6
	.long 	Vector7
	.long 	Vector8
	.long 	Vector9
	.long 	Vector10
	.long 	SVC_Handler
	.long	Vector12
	.long	Vector13
	.long	PendSV_Handler
	.long 	SysTick_Handler
	.long 	Vector15
	.long	Vector16
	.long	Vector17
	.long	Vector18
	.long	Vector19
	.long	Vector20
	.long	Vector21
	.long	Vector22
	.long	Vector23
	.long	Vector24
	.long	Vector25
	.long	Vector26
	.long	Vector27
	.long	Vector28
	.long	Vector29
	.long	Vector30
	.long	Vector31
	.long	Vector32
	.long	Vector33
	.long	Vector34
	.long	Vector35
	.long	Vector36



        .text

        .align      2
        .thumb_func
	.weak Reset_Handler
Reset_Handler:	
	b 	_crt0_entry
	
	.thumb_func
	.weak 	NMI_Handler
	.weak	HardFault_Handler
	.weak 	Vector4
	.weak 	Vector5
	.weak 	Vector6
	.weak 	Vector7
	.weak 	Vector8
	.weak 	Vector9
	.weak 	Vector10
	.weak 	SVC_Handler
	.weak	Vector12
	.weak	Vector13
	.weak	PendSV_Handler
	.weak 	SysTick_Handler
	.weak 	Vector15
	.weak	Vector16
	.weak	Vector17
	.weak	Vector18
	.weak	Vector19
	.weak	Vector20
	.weak	Vector21
	.weak	Vector22
	.weak	Vector23
	.weak	Vector24
	.weak	Vector25
	.weak	Vector26
	.weak	Vector27
	.weak	Vector28
	.weak	Vector29
	.weak	Vector30
	.weak	Vector31
	.weak	Vector32
	.weak	Vector33
	.weak	Vector34
	.weak	Vector35
	.weak	Vector36




	.thumb_func
NMI_Handler:
	.thumb_func
HardFault_Handler:
	.thumb_func
Vector4:
	.thumb_func
Vector5:
	.thumb_func
Vector6:
	.thumb_func
Vector7:
	.thumb_func
Vector8:
	.thumb_func
Vector9:
	.thumb_func
Vector10:
	.thumb_func
SVC_Handler:
	.thumb_func
Vector12:
	.thumb_func
Vector13:
	.thumb_func
PendSV_Handler:
	.thumb_func
SysTick_Handler:
	.thumb_func
Vector15:
	.thumb_func
Vector16:
	.thumb_func
Vector17:
	.thumb_func
Vector18:
	.thumb_func
Vector19:
	.thumb_func
Vector20:
	.thumb_func
Vector21:
	.thumb_func
Vector22:
	.thumb_func
Vector23:
	.thumb_func
Vector24:
	.thumb_func
Vector25:
	.thumb_func
Vector26:
	.thumb_func
Vector27:
	.thumb_func
Vector28:
	.thumb_func
Vector29:
	.thumb_func
Vector30:
	.thumb_func
Vector31:
	.thumb_func
Vector32:
	.thumb_func
Vector33:
	.thumb_func
Vector34:
	.thumb_func
Vector35:
	.thumb_func
Vector36:
	
	bl	_unhandled_exception
_unhandled_exception:
.loop:
	b	.loop


    