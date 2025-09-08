#include <stdio.h>

int main(int count, char **args)
{
	//// PHASE 1 ////
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

	if (count > 1) {
		for (int i = 1; i < count; i++)
			printf("%s\n", args[i]);
	}
	else
	{
		printf("no arguments provided\n");
	}
	return 0;
}
