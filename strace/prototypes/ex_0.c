#include <stdio.h>      /* printf */
#include <stdlib.h>     /* malloc */
#include <sys/wait.h>
#include <unistd.h>     /* fork */

int main(int count, char **args)
{
	pid_t parent = 0;
	int *wstatus = 0;

	if (count <= 1)
	{
		printf("no arguments\n");
		return 1;
	}

	parent = fork();
	if (parent) {
		// wait for child
		wstatus = malloc(sizeof(int));

		// for (int i = 1; i < count; i++)
			// call ptrace with request PTRACE_SINGLESTEP
			// this will suspend the tracee every time the register 'ip' changes
			// print 'single step' each iteration
			// printf("single step\n");

		// print child's exit status
		wait(wstatus);
		printf("Exit status: %d\n", *wstatus);
		free(wstatus);
	} else {
		// call ptrace with PTRACE_TRACEME
		execve(args[1], &args[1], NULL);
	}

	return 0;
}
