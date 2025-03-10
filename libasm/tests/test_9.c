#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "../libasm.h"

#define S1  "Holberton School"
#define S2  "HOLgERTON SCHOOL"
#define S3  "Holberton SchooL"
#define S4  "holbenotn socool"
#define S5  "HOLnonTON"
#define S6  "holberton"
#define S7  "HoLbErToN ScHoOl"
#define S8  "hOlBeRtOn sChOOL"

int main(void)
{
	int original, copycat;

	printf("\n%s\n%s\n", S1, S1);
	original = strncasecmp(S1, S1, 7);
	copycat = asm_strncasecmp(S1, S1, 7);
	assert(strncasecmp(S1, S1, 7) == asm_strncasecmp(S1, S1, 7));
	printf("original: %d\ncopycat: %d\n", original, copycat);

	printf("\n%s\n%s\n", S1, S2);
	original = strncasecmp(S1, S2, 6);
	copycat = asm_strncasecmp(S1, S2, 6);
	assert(strncasecmp(S1, S2, 6) == asm_strncasecmp(S1, S2, 6));
	printf("original: %d\ncopycat: %d\n", original, copycat);

	printf("\n%s\n%s\n", S1, S3);
	original = strncasecmp(S1, S3, 12);
	copycat = asm_strncasecmp(S1, S3, 12);
	assert(strncasecmp(S1, S3, 12) == asm_strncasecmp(S1, S3, 12));
	printf("original: %d\ncopycat: %d\n", original, copycat);

	printf("\n%s\n%s\n", S1, S4);
	original = strncasecmp(S1, S4, 8);
	copycat = asm_strncasecmp(S1, S4, 8);
	assert(strncasecmp(S1, S4, 8) == asm_strncasecmp(S1, S4, 8));
	printf("original: %d\ncopycat: %d\n", original, copycat);

	printf("\n%s\n%s\n", S3, S6);
	original = strncasecmp(S3, S6, 5);
	copycat = asm_strncasecmp(S3, S6, 5);
	assert(strncasecmp(S3, S6, 5) == asm_strncasecmp(S3, S6, 5));
	printf("original: %d\ncopycat: %d\n", original, copycat);

	printf("\n%s\n%s\n", S7, S8);
	original = strncasecmp(S7, S8, 4);
	copycat = asm_strncasecmp(S7, S8, 4);
	assert(strncasecmp(S7, S8, 4) == asm_strncasecmp(S7, S8, 4));
	printf("original: %d\ncopycat: %d\n", original, copycat);

	printf("\n%s\n%s\n", "", S6);
	original = strncasecmp("", S6, 2);
	copycat = asm_strncasecmp("", S6, 2);
	assert(strncasecmp("", S6, 2) == asm_strncasecmp("", S6, 2));
	printf("original: %d\ncopycat: %d\n", original, copycat);

	return (EXIT_SUCCESS);
}
