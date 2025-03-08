#include <stdlib.h>
#include <stdio.h>
#include "../libasm.h"

#define S1  "Holberton School"
#define S2  "hello world"
#define S3  "\0"

int main(void)
{
	size_t length;

	printf("size of size_t: %lu\n", sizeof(size_t));

	length = asm_strlen(S1);
	printf("string 1 length: %lu\n", length);
	length = asm_strlen(S2);
	printf("string 2 length: %lu\n", length);
	length = asm_strlen(S3);
	printf("string 3 length: %lu\n", length);

	return (length);
}
