#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void handle_sigint(int signum)
{
	fprintf(stdout, "Caught %d\n", signum);
	fflush(stdout);
}

/**
 * main - sets a handler for the 'SIGINT' signal, and exits right after the
 * signal has been received and handled
 *
 * Description: when a 'SIGINT' is received, 'Caught <signum>\n' is printed to
 * stdout and followed by 'Signal Received\n' and with exit 'EXIT_SUCCESS'
 *
 * Instructions:
 * - this program doesn't take an argument
 * - suspend indefinitely until a signal is received
 *       - the 'exit', 'sleep', and '_exit' functions are not allowed
 *       - no loops are allowed
 *
 * Return: exit codes
 */

int main(void)
{
	/* sigset_t wait_set; */
	/* struct sigaction new_sa; */

	/* new_sa.sa_handler = &handle_sigint; */
	/* sigaction(SIGINT, &new_sa, NULL); */
	signal(SIGINT, handle_sigint);

	/* sigemptyset(&wait_set); */
	/* sigaddset(&wait_set, SIGINT); */
	/* sigsuspend(&wait_set); */
	pause();

	fprintf(stdout, "Signal Received\n");
}
