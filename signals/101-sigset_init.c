#include <signal.h>
#include <sys/types.h>
#include "signals.h"

/**
 * sigset_init - a function that initializes a sigset
 * @set: a pointer to the signal set to initialize
 * @signals: a '0'-terminated array of 'int's, each being a signal number
 *
 * Return: 0 upon success or -1 upon failure
 */

int sigset_init(sigset_t *set, int *signals)
{
}
