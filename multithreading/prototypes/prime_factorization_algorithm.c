// #include <math.h>
#include <stdio.h>
#include <stdlib.h>

void
prime_factors(unsigned long number)
{
	unsigned long dividend = number, divisor = 2;

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
			/*
			 * alternatively, use a data structure to log multiples of previous
			 * divisors in order to skip them -- that is if we already tested 3
			 * we can then skip 9, 15, 21, ... (evens already skipped)
			 */
			if (divisor == 2)
				divisor++;
			else
				divisor += 2;
		}

	} while (divisor < dividend);

	if (dividend > 1)
		printf(" %lu\n", dividend);
}

int
main(int arg_c, char **arg_v)
{
	unsigned long number;

	number = strtol(arg_v[1], NULL, 10);
	prime_factors(number);

	return (0);
}
