#include "include/syscalls.h"
#include <signal.h>
#include <stdio.h>  /* printf */
#include <stdlib.h> /* malloc */
#include <sys/ptrace.h>
#include <sys/user.h> /* user_regs_struct */
#include <sys/wait.h>
#include <unistd.h> /* fork */

/* for every intercepted system call, print its name and it's return value in
 * hexadecimal, followed by a newline
 *
 * NOTE: it is impossible to retrieve the last system call's return value,
 * since it doesn't actually return. therefore, just print `?` as `strace` does
 */

void
print_syscall_return(struct user_regs_struct *syscall_regs)
{
	long long syscall_return = 0;

	if (syscall_regs->orig_rax != 231)
	{
		syscall_return = syscall_regs->rax;
		if (syscall_return != 0)
			fprintf(stderr, " = 0x%llx\n", syscall_return);
		else
			fprintf(stderr, " = %llu\n", syscall_return);
	}
	else
		fprintf(stderr, " = ?\n");
}

void
print_syscall_name(struct user_regs_struct *syscall_regs)
{
	static const type_t max_signals = 317;
	type_t syscall_code = syscall_regs->orig_rax;

	/* prevent invalids reads over syscalls_64_g */
	if (0 <= syscall_code && syscall_code <= max_signals)
	{
		fprintf(stderr, "%s", syscalls_64_g[syscall_code].name);
		fflush(stderr);
	}
}

void
print_syscall_info(pid_t parent, struct user_regs_struct *syscall_regs)
{
	static int syscall_exit = 1, first_syscall = 1;

	if (!syscall_exit && !first_syscall)
	{
		ptrace(PTRACE_GETREGS, parent, NULL, syscall_regs);
		print_syscall_name(syscall_regs);
	}
	else if (syscall_exit && !first_syscall)
	{
		ptrace(PTRACE_GETREGS, parent, NULL, syscall_regs);
		print_syscall_return(syscall_regs);
	}

	syscall_exit = !syscall_exit;

	if (first_syscall)
		first_syscall = 0;
}

int
main(int count, char **args)
{
	pid_t parent = 0;
	int wstatus = 0;
	struct user_regs_struct *syscall_regs;
	/* optimization. defining syscall_regs outside of print_syscall_info
	 * reduces malloc() and free() calls
	 */

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
			print_syscall_info(parent, syscall_regs);
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
