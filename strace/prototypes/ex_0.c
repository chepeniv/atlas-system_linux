#include <stdio.h>

int main(void)
{
	//// PHASE 1 ////
	//
	// parse arguments
	// call binary
	//
	//// PHASE 2 ////
	//
	// parse arguments
	// fork
	// if child:
	//     call ptrace with PTRACE_TRACEME
	//     use execve to execute given binary
	// if parent:
	//     wait for child
	//     loop
	//         call ptrace with request PTRACE_SINGLESTEP
	//         print 'single step' each iteration
	//     when done print child's exit status
	//
	//// NOTE ////
	///
	// PTRACE_SINGLESTEP suspends the tracee every time the register 'ip'
	// changes

	printf("hello, world!\n");
	return 0;
}
