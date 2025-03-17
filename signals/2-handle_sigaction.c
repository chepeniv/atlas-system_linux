#include "signals.h"
#include <stdio.h>
#include <signal.h>

/**
 * print_gotcha - prints gotcha message along with value received
 * @signum: number to print with message
 *
 * Description: satisfies the 'void (*sighandler_t)(int)' form needed to be
 * passed to the signal() call
 */

void print_gotcha(int signum)
{
	fprintf(stdout, "Gotcha! %d\n", signum);
	fflush(stdout);
}

/**
 * handle_sigaction - sets a new  handler for the `SIGINT` signal
 *
 * Description: - the handler prints 'Gotcha! [<signum>]\n' every time `Ctrl-C`
 * is pressed
 * restrictions: 'signal'(2) is not allowed
 *
 * Return: on success '0' ; on error '-1'
 */

int handle_sigaction(void)
{
	int result;
	struct sigaction new_sa;

	new_sa.sa_handler = &print_gotcha;

	result = sigaction(SIGINT, &new_sa, NULL);

	return (result);
}

