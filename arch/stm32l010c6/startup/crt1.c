/* 
	(c) - Iacopo Sprenger


 */

__attribute__((weak))
void __cpu_init(void) {
	//do nothing for cortex-m0+
}

__attribute__((weak))
void __early_init(void) {
	//do nothing for now
}

__attribute__((weak))
void __late_init(void) {
	//do nothing for now
}

__attribute__((noreturn, weak))
void __default_exit(void) {
	//lock processor in endless loop
	while (1) {
	}
}