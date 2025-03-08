#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../libasm.h"

#define S1  "Holberton School"
#define C1  'n'
#define C2  'S'
#define C3  's'

/**
 * main - Program entry point
 *
 * Return: EXIT_SUCCESS or EXIT_FAILURE
 */
int main(void)
{
	char *original, *copycat;

	original = strchr(S1, C1);
	copycat = asm_strchr(S1, C1);
	printf("original compare result: %s\n", original);
	printf("copycat compare result: %s\n", copycat);

	original = strchr(S1, C2);
	copycat = asm_strchr(S1, C2);
	printf("original compare result: %s\n", original);
	printf("copycat compare result: %s\n", copycat);

	original = strchr(S1, C3);
	copycat = asm_strchr(S1, C3);
	printf("original compare result: %s\n", original);
	printf("copycat compare result: %s\n", copycat);

	return (EXIT_SUCCESS);
}
