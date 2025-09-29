#include "list.h"
#include <stdlib.h>

/*
 * ******** INSTRUCTIONS ********
 * write a function that factorizes a number into a list of prime numbers
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
 * power - an exponentiation function
 * @base: number to raise
 * @exponent: the power to raise to
 *
 * Return: calculation
 */

unsigned long
power(unsigned long base, unsigned long exponent)
{
	unsigned long result = base;

	if (exponent < 1)
		return (1);

	while (exponent > 1)
	{
		result *= base;
		--exponent;
	}

	return (result);
}

/**
 * init_estimate - get a rough (order of magnitude) approximation of a square
 * root
 * @number: the number for which to find the estimate
 *
 * Return: calculation
 */

unsigned long
init_estimate(unsigned long number)
{
	unsigned long estimate, upper_bound = 1, lower_bound, twos = 0;

	while (upper_bound <= number && upper_bound * 2 != 0)
	{
		upper_bound *= 2;
		twos++;
	}

	if (twos % 2 == 0)
		twos /= 2;
	else
		twos = (twos - 1) / 2;

	upper_bound = power(2, twos + 1);
	lower_bound = power(2, twos);

	estimate = (upper_bound + lower_bound) / 2;

	return (estimate);
}

/**
 * sq_root - get an integer approximation of a number's square root
 * @number: the number for which to find this root
 *
 * Return: final square root calculation
 */

unsigned long
sq_root(unsigned long number)
{
	unsigned long left, right;

	left = init_estimate(number);

	do {
		right = number / left;
		left = (left + right) / 2;
	} while (right - left > 1);

	return (left);
}

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
	unsigned long number, sqrt_limit, dividend, divisor = 2;

	number = strtoul(s, NULL, 10);
	prime_factor_list = malloc(sizeof(list_t));
	list_init(prime_factor_list);

	if (number <= 2)
	{
		list_add_pfactor(prime_factor_list, number);
		return (prime_factor_list);
	}

	sqrt_limit = sq_root(number);
	dividend = number;

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
	} while (divisor <= sqrt_limit);

	if (dividend > 1)
		list_add_pfactor(prime_factor_list, dividend);

	return (prime_factor_list);
}
