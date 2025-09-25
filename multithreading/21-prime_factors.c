#include "list.h"
#include <math.h>
#include <stdlib.h>

/*
 * write a functions that factorizes a number into a list of prime numbers
 *
 * prototype: `list_t *prime_factors(char const *s);`
 *     `s` is the string representation of of the number to factorize
 *     this number will be positive and fit into an `unsigned long`
 *
 * code will be compiled with the file `list.c`
 * **note**: this task does not require multithreading and will not be linked
 * to the `pthread` library
 */

/**
 * list_add_pfactor - adds a given number to the given list
 * @list: list to append the number to
 * @number: number to handle and pass to list_add()
 */

void
list_add_pfactor(list_t *list, unsigned long number)
{
	unsigned long *content;

	content = malloc(sizeof(unsigned long));
	*content = number;
	list_add(list, content);
}

/**
 * prime_factors - find all prime factors of a given number and add these to a
 * list
 * @s: the string to interpret as an `unsigned long` to be prime factored
 *
 * Return: resultant list with all primes of the given `s`
 */

list_t *
prime_factors(char const *s)
{
	list_t *prime_factor_list;
	unsigned long number, sqrt_limit, dividend, divisor;

	number = strtoul(s, NULL, 10);
	prime_factor_list = malloc(sizeof(list_t));
	list_init(prime_factor_list);

	sqrt_limit = sqrt(number);
	dividend = number;
	divisor = 2;

	do {
		if (dividend % divisor == 0)
		{
			dividend /= divisor;
			list_add_pfactor(prime_factor_list, divisor);
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
		list_add_pfactor(prime_factor_list, dividend);

	return (prime_factor_list);
}
