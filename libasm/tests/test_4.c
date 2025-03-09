#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "../libasm.h"

#define S1  "Holberton School"
#define S2  "School"
#define S3  "Socool"

/**
 * main - Program entry point
 *
 * Return: EXIT_SUCCESS or EXIT_FAILURE
 */
int main(void)
{
	char *original, *copycat;

	original = strstr(S1, S2);
	copycat = asm_strstr(S1, S2);
	printf("original compare result: %s\n", original);
	printf("copycat compare result: %s\n", copycat);

	original = strstr(S1, S3);
	copycat = asm_strstr(S1, S3);
	printf("original compare result: %s\n", original);
	printf("copycat compare result: %s\n", copycat);

	original = strstr(S1, S1);
	copycat = asm_strstr(S1, S1);
	printf("original compare result: %s\n", original);
	printf("copycat compare result: %s\n", copycat);

	return (EXIT_SUCCESS);
}
