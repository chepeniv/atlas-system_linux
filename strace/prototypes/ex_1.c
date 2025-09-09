#include <signal.h>
#include <stdio.h>  /* printf */
#include <stdlib.h> /* malloc */
#include <sys/ptrace.h>
#include <sys/wait.h>
#include <unistd.h> /* fork */

int
main (int count, char **args)
{
    pid_t parent = 0;
    int *wstatus = 0;

    if (count <= 1)
    {
        printf ("no command provided\n");
        return 1;
    }

    parent = fork ();
    if (parent)
    {
        wstatus = malloc (sizeof (int));

        while (wait (wstatus) > -1)
        {
            printf ("single step\n");
            ptrace (PTRACE_SINGLESTEP, parent, 0, 0);
        }

        printf ("Exit status: %d\n", *wstatus);
        free (wstatus);
    }
    else
    {
        ptrace (PTRACE_TRACEME, 0, 0, 0);
        raise (SIGSTOP);
        execve (args[1], &args[1], NULL);
    }

    return 0;
}
