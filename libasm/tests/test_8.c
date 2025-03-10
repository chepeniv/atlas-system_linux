#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "../libasm.h"
#include "lorem_ipsum.h"

#define S1  "Holberton School"
#define S2  "HOLBERTON SCHOOL"
#define S3  "Holberton SchooL"
#define S4  "holberton socool"
#define S5  "HOLBERTON"
#define S6  "holberton"
#define S7  "HoLbErToN ScHoOl"
#define S8  "hOlBeRtOn sChOOL"

#define S8  "hOlBeRtOn sChOOL"

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

	printf("comparing:\n%s\n%s\n", S3, S6);
	original = strcasecmp(S3, S6);
	copycat = asm_strcasecmp(S3, S6);
	printf("original: %d\ncopycat: %d\n", original, copycat);

	printf("comparing:\n%s\n%s\n", S7, S8);
	original = strcasecmp(S7, S8);
	copycat = asm_strcasecmp(S7, S8);
	printf("original: %d\ncopycat: %d\n", original, copycat);

	original = strcasecmp(LOREM, LOREM);
	copycat = asm_strcasecmp(LOREM, LOREM);
	assert(strcasecmp(LOREM, LOREM) == asm_strcasecmp(LOREM, LOREM));
	printf("original: %d\ncopycat: %d\n", original, copycat);

	original = strcasecmp(LOREM, LOREM_B);
	copycat = asm_strcasecmp(LOREM, LOREM_B);
	printf("original: %d\ncopycat: %d\n", original, copycat);
	/* assert(strcasecmp(LOREM, LOREM_B) == strcasecmp(LOREM, LOREM_B)); */
	assert(strcasecmp(LOREM, LOREM_B) == asm_strcasecmp(LOREM, LOREM_B));

	return (EXIT_SUCCESS);
}
