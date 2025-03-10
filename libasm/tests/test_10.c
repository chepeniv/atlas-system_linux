#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "../libasm.h"

#define S1  "Holberton"
#define S2  "holberton"
#define S3  "HOLBERTON"

#define A1  "abcdefghijklmnopqrstuvwxyz"
#define A2  "ABCDEFGHIJKLMNOPQRSTUVWXYZ"

int main(void)
{
	int original, copycat;

	original = strspn(S2, A1);
	copycat = asm_strspn(S2, A1);
	printf("%s, %s\n", S2, A1);
	printf("%d, %d\n", original, copycat);

	original = strspn(S2, A2);
	copycat = asm_strspn(S2, A2);
	printf("%s, %s\n", S2, A2);
	printf("%d, %d\n", original, copycat);

	original = strspn(S3, A1);
	copycat = asm_strspn(S3, A1);
	printf("%s, %s\n", S3, A1);
	printf("%d, %d\n", original, copycat);

	original = strspn(S3, A2);
	copycat = asm_strspn(S3, A2);
	printf("%s, %s\n", S3, A2);
	printf("%d, %d\n", original, copycat);

	original = strspn(S1, A1);
	copycat = asm_strspn(S1, A1);
	printf("%s, %s\n", S1, A1);
	printf("%d, %d\n", original, copycat);

	original = strspn(S1, A2);
	copycat = asm_strspn(S1, A2);
	printf("%s, %s\n", S1, A2);
	printf("%d, %d\n", original, copycat);

	original = strspn(S1, A1 A2);
	copycat = asm_strspn(S1, A1 A2);
	printf("%s, %s\n", S1, A1 A2);
	printf("%d, %d\n", original, copycat);

	return (EXIT_SUCCESS);
}
