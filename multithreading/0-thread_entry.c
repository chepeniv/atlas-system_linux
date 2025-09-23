#include <stdio.h>
#include <pthread.h>

/*
 * write function that serves as the entry point into a new thread
 *
 * prototype: `void *thread_entry(void *arg);`
 *     `arg` holds the address of a string, followed by a newline, that must be
 *      printed
 *
 * respect the order of in which strings are printed out in the given examples
 */

/**
 * thread_entry - serves as an entry point for a thread. prints given data to
 * stdout
 *
 * @arg: data to interpret as a string
 * Return: pthread_exit(NULL);
 */

void *thread_entry(void *arg) {
	char *string_data = (char *) arg;

	printf("%s\n", string_data);
	pthread_exit(NULL);
}
