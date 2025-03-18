#include <signal.h>
#include <sys/types.h>
#include "signals.h"

/**
 * handle_pending - sets up a handler for all pending signals of the current
 * process
 * @handler: a pointer to the function to set for pending signals
 *
 * Instructions:
 * use of `signal` (2) is prohibited.
 *
 * Return: 0 upon success or -1 upon failure
 */

int handle_pending(int (*handler)(int))
{
}
