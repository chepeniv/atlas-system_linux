#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void
prime_factors(unsigned long number)
{
	unsigned long dividend = number, divisor = 2, sqrt_limit;

	sqrt_limit = sqrt(number);

	printf("=");
	do
	{
		if (dividend % divisor == 0)
		{
			dividend /= divisor;
			printf(" %lu x", divisor);
		}
		else
		{
			if (divisor == 2)
				divisor++;
			else
				divisor += 2;
		}
	} while (divisor < sqrt_limit);

	if (dividend > 1)
		printf(" %lu\n", dividend);
	else
		printf(" 1\n");
}

int
main(int arg_c, char **arg_v)
{
	unsigned long number;

	number = strtol(arg_v[1], NULL, 10);
	prime_factors(number);

	return (0);
}
