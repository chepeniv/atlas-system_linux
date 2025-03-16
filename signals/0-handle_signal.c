#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "signals.h"

/**
 * print_gotcha - prints gotcha message along with value received
 * @signum: number to print with message
 *
 * Description: satisfies the 'void (*sighandler_t)(int)' form needed to be
 * passed to the signal() call
 */

void print_gotcha(int signum)
{
	printf("Gotcha! %d\n", signum);
}

/**
 * handle_signal - sets a handler for the 'SIGINT' signal
 *
 * Description: prints 'Gotcha! [<signum>]\n' every time 'Ctrl-C' is pressed
 * wherein '<signum>' is signal number that was caught
 *
 * restrictions: 'sigaction'(2) is not allowed
 *
 * Return: (int) success '0'; error '-1'
 */

int handle_signal(void)
{
	void (*new_handler)(int);

	new_handler = signal(SIGINT, print_gotcha);
	if (new_handler == SIG_ERR)
		return (-1);

	return (0);
}
