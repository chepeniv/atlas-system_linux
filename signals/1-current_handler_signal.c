#include "signals.h"
#include <signal.h>
#include <stdlib.h>

/**
 * current_handler_signal - retrieve the current handler for the `SIGINT`
 * signal
 *
 * Description: the handler remains unchanged after calling this function
 * restrictions: `sigaction`(2) is not allowed
 *
 * Return: return a pointer to the current handler of `SIGINT` or `NULL` upon
 * failure
 */

void (*current_handler_signal(void))(int)
{
	void (*current_handler)(int);

	current_handler = signal(SIGINT, SIG_DFL);

	if (current_handler == SIG_ERR)
		return (NULL);
	if (signal(SIGINT, current_handler) == SIG_ERR)
		return (NULL);

	return (current_handler);
}
