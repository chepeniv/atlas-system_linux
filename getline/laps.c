#include <unistd.h>		/* read, write */
#include <stdlib.h>		/* malloc, realloc, free */
#include <string.h>		/* strcpy, strncpy, strdup, strcat; memset, memcpy */

#include "laps.h"

/*
 * task0 racing cars
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
 * if the function is called with `size = 0` free all allocated memory
 */

void race_state(int *id, size_t size);

/* {
 * static unsigned char * race_status = malloc(sizeof(unsigned char) * 64)
 * }
 */
