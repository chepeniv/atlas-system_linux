#include "signals.h"
#include <signal.h>
#include <stdlib.h>

/**
 * current_handler_signal - retrieve the current handler for the 'SIGINT'
 * signal
 *
 * Description: the handler remains unchanged after calling this function
 * restrictions: 'sigaction'(2) must be used; 'signal'(2) is not allowed
 *
 * Return: return a pointer to the current handler of 'SIGINT' or 'NULL' upon
 * failure
 */

void (*current_handler_sigaction(void))(int)
{
	void (*current_handler)(int);
	struct sigaction current_sa;
	struct sigaction probe_sa;

	probe_sa.sa_handler = SIG_DFL;

	sigaction(SIGINT, &probe_sa, &current_sa);
	current_handler = current_sa.sa_handler;

	if (current_handler == SIG_ERR)
		return (NULL);

	if (sigaction(SIGINT, &current_sa, NULL) == -1)
		return (NULL);

	return (current_handler);

}
