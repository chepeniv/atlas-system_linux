#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "../libasm.h"

#define S1  "Holberton School"
#define S2  "Sch"
#define S3  "Sohc"
#define S4  "erton"

/**
 * main - Program entry point
 *
 * Return: EXIT_SUCCESS or EXIT_FAILURE
 */

int main(void)
{
	char *original, *copycat;

	original = strstr(S1, S4);
	copycat = asm_strstr(S1, S4);
	printf("original : %s\n", original);
	printf("copycat  : %s\n", copycat);

	original = strstr(S1, S3);
	copycat = asm_strstr(S1, S3);
	printf("original : %s\n", original);
	printf("copycat  : %s\n", copycat);

	original = strstr(S1, S1);
	copycat = asm_strstr(S1, S1);
	printf("original : %s\n", original);
	printf("copycat  : %s\n", copycat);

	original = strstr(S1, S2);
	copycat = asm_strstr(S1, S2);
	printf("original : %s\n", original);
	printf("copycat  : %s\n", copycat);

	original = strstr("hello world", "");
	copycat = asm_strstr("hello world", "");
	printf("original : %s\n", original);
	printf("copycat  : %s\n", copycat);

	original = strstr("", "");
	copycat = asm_strstr("", "");
	printf("original : %s\n", original);
	printf("copycat  : %s\n", copycat);

	return (EXIT_SUCCESS);
}
