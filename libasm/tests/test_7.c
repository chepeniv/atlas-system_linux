#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "../libasm.h"

int main(void)
{
	size_t wlen, total;

	wlen = asm_puts("H");
	total = wlen;

	wlen = asm_puts("olberton");
	total += wlen;

	wlen = asm_puts(" School\n");
	total += wlen;

	printf("total written: %lu\n", total);

	return (EXIT_SUCCESS);
}
