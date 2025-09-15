#include "include/syscalls.h"
#include <signal.h>
#include <stdio.h>  /* printf */
#include <stdlib.h> /* malloc */
#include <sys/ptrace.h>
#include <sys/user.h> /* user_regs_struct */
#include <sys/wait.h>
#include <unistd.h> /* fork */

// for every intercepted system call, print its name followed by a newline
// no need to handle the `PATH`: `command` will be given as a full path to a
// binary

void
print_syscall(struct user_regs_struct *syscall_regs)
{
	static const type_t max_signals = 317;
	type_t syscall_code = syscall_regs->orig_rax;

	/* prevent invalids reads over syscalls_64_g */
	if (0 <= syscall_code && syscall_code <= max_signals)
	{
		fprintf(stderr, "%s\n", syscalls_64_g[syscall_code].name);
		fflush(stderr);
	}
}

int
main(int count, char **args)
{
	pid_t parent = 0;
	int wstatus = 0, syscall_enter = 0, first_syscall = 1;
	struct user_regs_struct *syscall_regs;

	if (count <= 1)
	{
		printf("no command provided\n");
		return (1);
	}

	parent = fork();
	if (parent)
	{
		syscall_regs = malloc(sizeof(struct user_regs_struct));

		wait(&wstatus);
		do
		{
			ptrace(PTRACE_SYSCALL, parent, NULL, NULL);
			wait(&wstatus);

			if (syscall_enter && !first_syscall)
			{
				ptrace(PTRACE_GETREGS, parent, NULL, syscall_regs);
				print_syscall(syscall_regs);
			}

			syscall_enter = !syscall_enter;
			if (first_syscall)
				first_syscall = 0;
		} while (!WIFEXITED(wstatus));

		free(syscall_regs);
	}
	else
	{
		ptrace(PTRACE_TRACEME, NULL, NULL, NULL);
		raise(SIGCHLD);
		execve(args[1], &args[1], NULL);
	}

	return (0);
}
