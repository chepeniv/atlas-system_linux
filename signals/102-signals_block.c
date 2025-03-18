#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include "signals.h"

/**
 * signals_block - blocks a given set of signals from being delivered to the
 * current process
 * @signals: a `0`-terminated array of `int`s, each being a signal number
 * to block
 *
 * Instructions:
 * use of either `signal` (2) and `sigaction` (2) is prohibited.
 *
 * Return: 0 upon success or -1 upon failure
 */

int signals_block(int *signals)
{
	sigset_t set;
	int result;

	sigemptyset(&set);

	for (int s = 0; signals[s]; s++)
		result = sigaddset(&set, signals[s]);

	result = sigprocmask(SIG_SETMASK, &set, NULL);

	return (result);
}
