#include <stdio.h>      /* printf */
#include <stdlib.h>     /* malloc */
#include <sys/wait.h>
#include <unistd.h>     /* fork */
#include <sys/ptrace.h>

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

		// call ptrace with request PTRACE_SINGLESTEP
		// this will suspend the tracee every time the register 'ip' changes
		while(wait(wstatus) > -1)
		{
			ptrace(PTRACE_TRACEME, 0, 0, 0);
			printf("single step\n");
		}

		// print child's exit status
		wait(wstatus);
		printf("Exit status: %d\n", *wstatus);
		free(wstatus);
	} else {
		ptrace(PTRACE_TRACEME, 0, 0, 0);
		execve(args[1], &args[1], NULL);
	}

	return 0;
}
