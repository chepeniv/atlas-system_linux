#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/**
 * main - a program that outputs a description for the given signal
 * @count: total number of parameters passed
 * @arguments: NULL terminated double char pointer array referencing the passed
 * arguments
 *
 * usage: './describe <signum>'
 *
 * instructions:
 * - if an incorrect number of arguments is given, print 'Usage: %s <signum>\n'
 *   where '%s' is given by 'argv[0]' and exit with 'EXIT_FAILURE'
 * - no more than one function in your file
 * - no more than twelve lines in your function
 * - assume all parameters given will be numbers
 *
 * output: if the signal is found print '<signum>: Description\n' else print
 * '<signum>: Unknown signal <signum>\n'
 *
 * Return: integer exit code
 */

int main(int count, char **arguments)
{
	if (count != 2)
	{
		printf("Usage: %s <signum>\n", arguments[0]);
		return (EXIT_FAILURE);
	}
	int code = atoi(arguments[1]);
	char *desc = strsignal(code);

	if (desc)
		printf("%d: %s\n", code, desc);
	else
		printf("%d: Unknown signal %d\n", code, code);
}
