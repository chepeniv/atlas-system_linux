#include "list.h"
#include <stdlib.h>
#include <math.h>

/*
 * write a functions that factorizes a number into a list of prime numbers
 *
 * prototype: `list_t *prime_factors(char const *s);`
 *     `s` is the string representation of of the number to factorize
 * 	   this number will be positive and fit into an `unsigned long`
 *
 * code will be compiled with the file `list.c`
 * **note**: this task does not require multithreading and will not be linked
 * to the `pthread` library
 */

/**
 * prime_factors -
 * @s:
 *
 * Return: list_t
 */

list_t *prime_factors(char const *s)
{
	list_t *prime_factor_list;
	unsigned long number, sqrt_limit, even;
	/* char *endptr; */

	number = strtol(s, NULL, 10);
	sqrt_limit = (unsigned long) sqrt((double) number);
	prime_factor_list = list_init(prime_factor_list);

	/*
	 * DIVIDEND = NUMBER
	 * DIVISOR = 2
	 *
	 * while DIVISOR < SQRT(DIVIDEND)
	 *     if DIVIDEND modulo DIVISOR = 0
	 *         append DIVISOR to PFACTOR_LIST
	 *         DIVIDEND /= DIVISOR
	 *     else
	 *         if DIVISOR == 2
	 *             DIVISOR++
	 *         else
	 *             DIVISOR += 2
	 *
	 */

	return (prime_factor_list);
}
