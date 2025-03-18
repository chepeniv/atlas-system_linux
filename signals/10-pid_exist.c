#include <signal.h>
#include <sys/types.h>

/**
 * pid_exist - test if a process exists given its pid
 * @pid: process id number to investigate
 *
 * Instructions:
 * no more than one function in your file.
 * no more than one line in your function.
 * no more than two headers in your file.
 * your 'signals.h' is not allowed.
 * the 'getpgid' function is not allowed.
 *
 * Return: if the process with the given pid exist '1' is returned, otherwise
 * '0'
 */

int pid_exist(pid_t pid)
{
	return (kill(pid, SIGCHLD) + 1);
}
