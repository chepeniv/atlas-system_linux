#include <stdio.h>
#include <stdlib.h>
#include "asm_add.h"

int main(int n, char **v)
{
	int a, b, c;

	if (n >= 3)
	{
		a = atoi(v[1]);
		b = atoi(v[2]);
	}
	else
	{
		printf("insufficient parameters given\n");
		return (1);
	}

	if (!a || !b)
	{
		printf("failed integer conversion or zero supplied\n");
		return (1);
	}

	c = asm_dbl(a);
	printf("result of asm_dbl(%d) is %d\n", a, c);
	c = asm_add(a, b);
	printf("result of asm_add(%d, %d) is %d\n", a, b, c);
	return (0);
}
