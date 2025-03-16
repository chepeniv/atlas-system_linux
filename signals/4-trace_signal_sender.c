#include "signals.h"
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>

/**
 * handler_print_sender - prints 'SIGQUIT sent by <pid>\n' each time 'SIGQUIT'
 * and only 'SIGQUIT' is caught
 * @sig_num: the signal number caught
 * @sig_info: metadata about the signal caught
 * @sig_context: ucontext
 */

void sig_handler_print_sender(
int        sig_num,
siginfo_t *sig_info,
void      *sig_context)
{
	(void) sig_num;
	(void) sig_context;

	printf("SIGQUIT sent by %d\n", sig_info->si_pid);
}

/**
 * trace_signal_sender - sets up a handler for the `SIGQUIT` signal
 *
 * Description: the handler prints 'SIGQUIT sent by <pid>\n' each time
 * 'SIGQUIT' and only 'SIGQUIT' is caught
 *
 * Return: on success '0'; on error '-1'
 */

int trace_signal_sender(void)
{
	int result;
	struct sigaction new_sa;

	new_sa.sa_sigaction = &sig_handler_print_sender;
	new_sa.sa_flags = SA_SIGINFO;

	result = sigaction(SIGQUIT, &new_sa, NULL);

	return (result);
}
