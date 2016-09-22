.section ".text.startup"

.global _start
.global _get_stack_pointer

_start:
	// set stack pointer at 64MB (our applications will not
	// crash into this(?) and it will be available to the CPU
	ldr sp, =(64 * 1024 * 1024)

	// c startup function: won't return and will call main
	b _cstartup

_inf_loop:
	b _inf_loop
