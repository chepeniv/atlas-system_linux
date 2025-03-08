#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../libasm.h"

#define S1  "Holberton School"
#define S2  "Hello"
#define S3  "Holbarton Socool"

int main(void)
{
	int original, copycat;

	original = strncmp(S1, S1, 6);
	copycat = asm_strncmp(S1, S1, 6);
	printf("\nstrings: %s -- %s \n", S1, S1);
	printf("original compare result: %d\n", original);
	printf("copycat compare result: %d\n", copycat);

	original = strncmp(S1, S2, 6);
	copycat = asm_strncmp(S1, S2, 6);
	printf("\nstrings: %s -- %s \n", S1, S2);
	printf("original compare result: %d\n", original);
	printf("copycat compare result: %d\n", copycat);

	original = strncmp(S1, S3, 6);
	copycat = asm_strncmp(S1, S3, 6);
	printf("\nstrings: %s -- %s \n", S1, S3);
	printf("original compare result: %d\n", original);
	printf("copycat compare result: %d\n", copycat);

	original = strncmp(S3, S1, 6);
	copycat = asm_strncmp(S3, S1, 6);
	printf("\nstrings: %s -- %s \n", S3, S1);
	printf("original compare result: %d\n", original);
	printf("copycat compare result: %d\n", copycat);

	return (EXIT_SUCCESS);
}
