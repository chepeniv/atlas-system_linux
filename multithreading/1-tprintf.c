#include <pthread.h>
#include <stdarg.h>
#include <stdio.h>

/*
 * INSTRUCTIONS:
 *
 * create a function that uses any `printf` function to output a given
 * formatted string
 *
 * prototype: `int tprintf(char const *format, ...);`
 *     output must be preceded by the calling thread ID like so:
 *     `[thread_id] formatted_string\n`
 */

/**
 * tprintf - output the id of the current thread followed by a formatted string
 *
 * @format: string to format
 * Return: 0 upon successful execution
 */

int
tprintf(char const *format, ...)
{
	va_list args;
	pthread_t thread_id;

	thread_id = pthread_self();
	va_start(args, format);

	/*
	 * alternatively, duplicate `format` on a buffer and use `sprintf()` before
	 * sending that buffer to printf
	 */

	printf("[%lu] ", thread_id);
	printf(format, args);

	va_end(args);

	return (0);
}
