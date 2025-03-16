#include "signals.h"
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>

static desc_index sig_desc_index[] = {
	{SIGINT,    "Interactive attention"},
	{SIGILL,    "Illegal"},
	{SIGABRT,   "Abnormal Termination"},
	{SIGFPE,    "Floating Point Error"},
	{SIGSEGV,   "Segment Violation"},
	{SIGTERM,   "Termination Request"},
	{SIGHUP,    "Hangup"},
	{SIGQUIT,   "Quit"},
	{SIGTRAP,   "Breakpoint trap"},
	{SIGKILL,   "Kill"},
	{SIGPIPE,   "Broken pipe"},
	{SIGALRM,   "Alarm clock"},
	{SIGPOLL,   "I/O now possible"},
	{SIGSTKFLT, "Stack fault (obsolete)"},
	{SIGPWR,    "Power failure imminent"},
	{SIGBUS,    "Bus error"},
	{SIGSYS,    "Bad system call"},
	{SIGURG,    "Urgent data is available at a socket"},
	{SIGSTOP,   "Stop, unblockable"},
	{SIGTSTP,   "Keyboard stop"},
	{SIGCONT,   "Continue"},
	{SIGCHLD,   "Child terminated or stopped"},
	{SIGTTIN,   "Background read from control terminal"},
	{SIGTTOU,   "Background write to control terminal"},
	{SIGPOLL,   "Pollable event occurred"},
	{SIGXFSZ,   "File size limit exceeded"},
	{SIGXCPU,   "CPU time limit exceeded"},
	{SIGVTALRM, "Virtual timer expired"},
	{SIGPROF,   "Profiling timer expired"},
	{SIGUSR1,   "User-defined signal 1"},
	{SIGUSR2,   "User-defined signal 2"},
	{SIGWINCH,  "Window size change"},
	{-1, NULL}
};

/**
 * main - a program that outputs a description for the given signal
 * @count: total number of parameters passed
 * @arguments: NULL terminated double char pointer array referencing the passed
 * arguments
 *
 * usage: './describe <signum>'
 *
 * instructions:
 * - if an incorrect number of arguments is given, print 'Usage: %s <signum>\n'
 *   where '%s' is given by 'argv[0]' and exit with 'EXIT_FAILURE'
 * - no more than one function in your file
 * - no more than twelve lines in your function
 * - assume all parameters given will be numbers
 *
 * output: if the signal is found print '<signum>: Description\n' else print
 * '<signum>: Unknown signal <signum>\n'
 *
 * Return: integer exit code
 */

int main(int count, char **arguments)
{
	int code = atoi(arguments[1]);

	if (count != 2)
	{
		printf("Usage: %s <signum>\n", arguments[0]);
		return (EXIT_FAILURE);
	}
	for (int i = 0; sig_desc_index[i].desc; i++)
		if (code == sig_desc_index[i].code)
		{
			printf("%d: %s\n", sig_desc_index[i].code, sig_desc_index[i].desc);
			return (EXIT_SUCCESS);
		}
	printf("%d: Unknown signal %d\n", code, code);
	return (EXIT_SUCCESS);
}
