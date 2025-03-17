#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
/* #include <linux/signal.h> */
/* #include <sys/syscall.h> */
/* #include <unistd.h> */

/**
 * main - a program that sends the 'SIGINT' signal to a process given by its
 * PID
 * @count: total number of parameters passed
 * @arguments: NULL terminated double char pointer array referencing the passed
 * arguments
 *
 * Usage:
 *     ./signal_send <pid>
 *     - <pid>' will not be '0'
 *
 * Instructions:
 *     - no more than one function in your file
 *
 * Output:
 *     if an incorrect number of arguments is given, print 'Usage: %s <pid>\n'
 *         - '%s' is given by 'argv[0]'
 *         - exit with 'EXIT_FAILURE'
 *
 * Return: exit codes
 */

int main(int count, char **arguments)
{
	int target_pid;

	if (count != 2)
	{
		printf("Usage: %s <pid>\n", arguments[0]);
		return (EXIT_FAILURE);
	}

	/* syscall(SYS_pidfd_send_signal, target_pid, SIGINT, NULL, 0); */
	target_pid = atoi(arguments[1]);
	kill(target_pid, SIGINT);
}
