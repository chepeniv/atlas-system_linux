#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "../libasm.h"

#define S1  "Holberton"
#define S2  "holberton"
#define S3  "HOLBERTON"

#define A1  "nopqrstuvwxyz"
#define A2  "ABCDEFG"
#define A3  "()[]{}<>e"

int main(void)
{
	char const *original, *copycat;

	original = strpbrk(S2, A1);
	copycat = asm_strpbrk(S2, A1);
	printf("%s -- %s\n", original, copycat);

	original = strpbrk(S2, A2);
	copycat = asm_strpbrk(S2, A2);
	printf("%s -- %s\n", original, copycat);

	original = strpbrk(S3, A1);
	copycat = asm_strpbrk(S3, A1);
	printf("%s -- %s\n", original, copycat);

	original = strpbrk(S3, A2);
	copycat = asm_strpbrk(S3, A2);
	printf("%s -- %s\n", original, copycat);

	original = strpbrk(S1, A3);
	copycat = asm_strpbrk(S1, A3);
	printf("%s -- %s\n", original, copycat);

	return (EXIT_SUCCESS);
}
