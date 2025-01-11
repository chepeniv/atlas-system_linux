#include <unistd.h>		/* read, write */
#include <stdlib.h>		/* malloc, realloc, free */
#include <string.h>		/* strcpy, strncpy, strdup, strcat; memset, memcpy */
#include <stdio.h>		/* REMOVE AFTER TESTING */
#include "laps.h"

#define LENGTH_OF(arr) sizeof(arr) / sizeof(*arr)

/* task0 racing cars
 * write a function which keeps track of laps made by each car in a race
 *
 * `id` (an array of ints) represents the identifier for each car
 * `size` is the length of this array
 *
 * each identifier is expected to be unique
 *
 * if an identifier is unknown create a new car with laps = 0 and print
 * "Car X joined the race\n"
 *
 * each time the function is called, the number of laps for each car in `id`
 * must be incremented by 1. print the state of the race.
 * "Race state:\n"
 * sort cars by their identifier and print "Car X [Y laps]
 *
 */

void print_int_array(int * numbers, int length)
{
	int i;

	putchar('[');
	for (i = 0; i < length - 1; i++)
		printf("%d, ", numbers[i]);
	printf("%d", numbers[i]);
	printf("] ");
}

void race_state(int *id, size_t length){
	if (length == 0) {
		/* if size is 0 free all allocated memory */
		return;
	}

	print_int_array(id, length);
}

int main(void) {
	int car_ids[3] = {2, 5, 7};
	int length = LENGTH_OF(car_ids);

	race_state(car_ids, length);

	return 0;
}
