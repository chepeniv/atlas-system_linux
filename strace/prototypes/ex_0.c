#include <stdio.h>      /* printf */
#include <stdlib.h>     /* malloc */
#include <sys/wait.h>
#include <unistd.h>     /* fork */

int main(int count, char **args)
{
	// NOTE : PTRACE_SINGLESTEP suspends the tracee every time the register 'ip'
	// changes

	pid_t parent = 0;
	int *wstatus = 0;

	if (count <= 1)
	{
		printf("no arguments provided\n");
		return 1;
	}

	parent = fork();

	if (parent) {
		// wait for child
		// loop
		//     call ptrace with request PTRACE_SINGLESTEP
		//     print 'single step' each iteration
		// print child's exit status
		printf("this is the parent process\n");

		wstatus = malloc(sizeof(int));
		wait(wstatus);
		printf("wait status: %d\n", *wstatus);
		free(wstatus);

		for (int i = 1; i < count; i++)
			printf("parent: %s\n", args[i]);
	} else {
		// call ptrace with PTRACE_TRACEME
		// use execve to execute given binary
		printf("this is the child process\n");
		for (int i = 1; i < count; i++)
			printf("child: %s\n", args[i]);
	}

	return 0;
}
