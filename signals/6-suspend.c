#include <signal.h>
#include <stdio.h>
#include <unistd.h>

/**
 * handle_sigint - prints a simple message to stdout
 * @signum: number to output with message
 */

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
	signal(SIGINT, handle_sigint);
	pause();
	fprintf(stdout, "Signal received\n");
}
