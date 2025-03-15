#include "signals.h"

/**
 * a function that sets a handler for the 'SIGINT' signal
 * return '0' on success or '-1' on error
 *
 * print 'Gotcha! [<signum>]\n' every time 'Ctrl-C' is pressed ('<signum>' is
 * signal number that was caught)
 *
 * 'sigaction'(2) is not allowed
 */

int handle_signal(void) {
	return (0);
}
