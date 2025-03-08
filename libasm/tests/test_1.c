#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../libasm.h"

#define S1  "Holberton School"
#define S2  ""
#define S3  "Holberton Socool"

int main(void)
{
	int original, copycat;

	original = strcmp(S1, S1);
	copycat = asm_strcmp(S1, S1);
	printf("\nstrings: %s -- %s \n", S1, S1);
	printf("original compare result: %d\n", original);
	printf("copycat compare result: %d\n", copycat);

	original = strcmp(S1, S2);
	copycat = asm_strcmp(S1, S2);
	printf("\nstrings: %s -- %s \n", S1, S2);
	printf("original compare result: %d\n", original);
	printf("copycat compare result: %d\n", copycat);

	original = strcmp(S1, S3);
	copycat = asm_strcmp(S1, S3);
	printf("\nstrings: %s -- %s \n", S1, S3);
	printf("original compare result: %d\n", original);
	printf("copycat compare result: %d\n", copycat);

	original = strcmp(S3, S1);
	copycat = asm_strcmp(S3, S1);
	printf("\nstrings: %s -- %s \n", S3, S1);
	printf("original compare result: %d\n", original);
	printf("copycat compare result: %d\n", copycat);

	return (EXIT_SUCCESS);
}
