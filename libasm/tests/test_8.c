#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "../libasm.h"

#define S1  "Holberton School"
#define S2  "HOLBERTON SCHOOL"
#define S3  "Holberton SchooL"
#define S4  "holberton socool"

int main(void)
{
	int original, copycat;

	printf("comparing:\n%s\n%s\n", S1, S1);
	original = strcasecmp(S1, S1);
	copycat = asm_strcasecmp(S1, S1);
	printf("original: %d\ncopycat: %d\n", original, copycat);

	printf("comparing:\n%s\n%s\n", S1, S2);
	original = strcasecmp(S1, S2);
	copycat = asm_strcasecmp(S1, S2);
	printf("original: %d\ncopycat: %d\n", original, copycat);

	printf("comparing:\n%s\n%s\n", S1, S3);
	original = strcasecmp(S1, S3);
	copycat = asm_strcasecmp(S1, S3);
	printf("original: %d\ncopycat: %d\n", original, copycat);

	printf("comparing:\n%s\n%s\n", S1, S4);
	original = strcasecmp(S1, S4);
	copycat = asm_strcasecmp(S1, S4);
	printf("original: %d\ncopycat: %d\n", original, copycat);

	return (EXIT_SUCCESS);
}
