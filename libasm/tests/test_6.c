#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "../libasm.h"

int main(void)
{
	int value;

	value = asm_putc('H');
	printf("\n%d\n", value);

	value = asm_putc('b');
	printf("\n%d\n", value);

	value = asm_putc('t');
	printf("\n%d\n", value);

	value = asm_putc('n');
	printf("\n%d\n", value);

	value = asm_putc('\n');
	printf("\n%d\n", value);

	return (EXIT_SUCCESS);
}
