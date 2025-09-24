#include <pthread.h>
#include <stdarg.h>
#include <stdio.h>

pthread_mutex_t mlock_print;

/*
 * INSTRUCTIONS:
 *
 * write a function that uses any `printf` function to output a given formatted
 * string
 *
 * you must use `mutex` locks to avoid race conditions,
 *
 * the `mutex` needs to be initialized and destroyed, but without having to do
 * that in our main.c
 *
 * prototype: `int tprintf(char const *format, ...);`
 *
 * output must be preceded by the calling thread ID
 * tip: global variables are allowed
 * run Betty with `--allow-global-variables`
 */

/* placed gcc attribute here for betty to correctly parse func doc */
__attribute__((constructor))
/**
 * setup_mlocks - initialize needed mutex locks so that the main function
 * doesn't have to
 */
void
setup_mlocks(void)
{
	pthread_mutex_init(&mlock_print, NULL);
}

__attribute__((destructor))
/**
 * teardown_mlocks - free mutex lock resources so that the main function
 * doesn't have to
 */
void
teardown_mlocks(void)
{
	pthread_mutex_destroy(&mlock_print);
}

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

	pthread_mutex_lock(&mlock_print);
		fflush(stdout);
		printf("[%lu] ", thread_id);
		printf(format, args);
	pthread_mutex_unlock(&mlock_print);

	va_end(args);

	return (0);
}
