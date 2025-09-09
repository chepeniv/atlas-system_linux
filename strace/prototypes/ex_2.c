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
    int *wstatus = 0, syscall_exit = 0;
    struct user_regs_struct *syscall_regs;

    if (count <= 1)
    {
        printf("no command provided\n");
        return 1;
    }

    parent = fork();
    if (parent)
    {
        wstatus = malloc(sizeof(int));
        syscall_regs = malloc(sizeof(struct user_regs_struct));

        /* ptrace(request, pid, addr, data) */
        while (wait(wstatus) > -1)
        {
            if (!syscall_exit)
            {
                ptrace(PTRACE_GETREGS, parent, 0, syscall_regs);
                printf("[ %llu ]\n", syscall_regs->orig_rax);
            }
            ptrace(PTRACE_SYSCALL, parent, 0, 0);
            syscall_exit = !syscall_exit;
        }

        printf("Exit status: %d\n", *wstatus);

        free(syscall_regs);
        free(wstatus);
    }
    else
    {
        ptrace(PTRACE_TRACEME, 0, 0, 0);
        // raise (SIGSTOP);
        execve(args[1], &args[1], NULL);
    }

    return 0;
}
