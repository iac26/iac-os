/*
	STM32L010C6 Memory layout
*/

ENTRY(Reset_Handler)


MEMORY {

	FLASH    (rx) : org = 0x08000000, len = 32k
	RAM     (rwx) : org = 0x20000000, len = 8k
}


__process_stack_size__ = 0x400;
__main_stack_size__ = 0x400;


SECTIONS {

	.isr_vector : 
	{
		. = ALIGN(4);
		KEEP(*(.isr_vector)) /* Startup code */
		. = ALIGN(4);
	} >FLASH

	.text : ALIGN_WITH_INPUT
	{
		__text_base__ = .;
		*(.text)           /* .text sections (code) */
		*(.text*)          /* .text* sections (code) */
		*(.glue_7)         /* glue arm to thumb code */
		*(.glue_7t)        /* glue thumb to arm code */
		*(.eh_frame)

		KEEP (*(.init))
		KEEP (*(.fini))

		. = ALIGN(4);
		__text_end__ = .;        /* define a global symbols at end of code */
	} >FLASH

	  /* Constant data into "FLASH" Rom type memory */
	.rodata : 
	{
		__rodata_base__ = .;
		*(.rodata)         /* .rodata sections (constants, strings, etc.) */
		*(.rodata*)        /* .rodata* sections (constants, strings, etc.) */
		. = ALIGN(4);
		__rodata_end__ = .;
	} >FLASH

	  /* Used by the startup to initialize data */
  	

	.data : ALIGN(4)
	{
		__textdata_base__ = LOADADDR(.data);
		__data_base__ = .;        /* create a global symbol at data start */
		*(.data)           /* .data sections */
		*(.data*)          /* .data* sections */
		*(.ramtext)        /* .tamtext sections */
		. = ALIGN(4);
		__data_end__ = .;        /* define a global symbol at data end */

	} >RAM AT> FLASH

	.bss (NOLOAD): ALIGN(4)
	{
		/* This is used by the startup in order to initialize the .bss section */
		__bss_base__ = .;
		*(.bss)
		*(.bss*)
		*(COMMON)
		. = ALIGN(4);
		__bss_end__ = .;
	} >RAM

	/* Special section for exceptions stack.*/
	.mstack (NOLOAD) :
	{
	. = ALIGN(8);
	__main_stack_base__ = .;
	. += __main_stack_size__;
	. = ALIGN(8);
	__main_stack_end__ = .;
	} > RAM

	/* Special section for process stack.*/
	.pstack (NOLOAD) :
	{
	. = ALIGN(8);
	__process_stack_base__ = .;
	. += __process_stack_size__;
	. = ALIGN(8);
	__process_stack_end__ = .;
	} > RAM

}


