#include <stdio.h>
#include <unistd.h>

int main(int count, char **args)
{
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

	pid_t parent = 0;

	parent = fork();

	if (count <= 1)
	{
		printf("no arguments provided\n");
		return 1;
	}

	if (parent) {
		printf("this is the parent process\n");
		for (int i = 1; i < count; i++)
			printf("parent: %s\n", args[i]);
	} else {
		printf("this is the child process\n");
		for (int i = 1; i < count; i++)
			printf("child: %s\n", args[i]);
	}

	return 0;
}
