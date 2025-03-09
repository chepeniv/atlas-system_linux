#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "../libasm.h"

int main(void)
{
	int value;

	value = asm_putc('H');
	value = asm_putc('b');
	value = asm_putc('t');
	value = asm_putc('n');
	value = asm_putc('\n');
	printf("%d\n", value);

	return (EXIT_SUCCESS);
}
