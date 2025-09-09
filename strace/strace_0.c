#include <signal.h>
#include <stdio.h>  /* printf */
#include <stdlib.h> /* malloc */
#include <sys/ptrace.h>
#include <sys/user.h> /* user_regs_struct */
#include <sys/wait.h>
#include <unistd.h> /* fork */

int
main(int count, char **args)
{
	pid_t parent = 0;
	int *wstatus = 0, syscall_enter = 0;
	struct user_regs_struct *syscall_regs;

	if (count <= 1)
	{
		printf("no command provided\n");
		return (1);
	}

	parent = fork();
	if (parent)
	{
		wstatus = malloc(sizeof(int));
		syscall_regs = malloc(sizeof(struct user_regs_struct));

		wait(wstatus);
		do {
			ptrace(PTRACE_SYSCALL, parent, NULL, NULL);
			wait(wstatus);

			if (syscall_enter)
			{
				ptrace(PTRACE_GETREGS, parent, NULL, syscall_regs);
				printf("%llu\n", syscall_regs->orig_rax);
			}
			syscall_enter = !syscall_enter;
		} while (!WIFEXITED(*wstatus));

		free(syscall_regs);
		free(wstatus);
	}
	else
	{
		ptrace(PTRACE_TRACEME, 0, 0, 0);
		raise(SIGSTOP);
		execve(args[1], &args[1], NULL);
	}

	return (0);
}
