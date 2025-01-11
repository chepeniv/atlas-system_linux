#include <unistd.h>		/* read, write */
#include <stdlib.h>		/* malloc, realloc, free */
#include <string.h>		/* strcpy, strncpy, strdup, strcat; memset, memcpy */
#include "laps.h"

#define LENGTH_OF(arr) sizeof(arr) / sizeof(*arr)

/*
 * keep track of the number of laps made by each car
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
 * if size is 0 free all allocated memory
 */

void race_state(int *racers, size_t number_of){
	if (number_of == 0) {
		return;
	}

	static int lap_tracker[128] = {[0 ... 127] = -1};
	sort_array(racers, number_of);

	for (size_t i = 0; i < number_of; i++)
	{
		int contestant = racers[i];
		lap_tracker[contestant] = lap_tracker[contestant] + 1;
		printf(
			"contestant %d completed %d laps\n",
			contestant,
			lap_tracker[contestant]);
	}
}

int main(void) {
	int car_ids[3] = {2, 5, 7};
	int car_ids_2[5] = {10, 4, 3, 11, 44};
	int length = LENGTH_OF(car_ids);
	int length_2 = LENGTH_OF(car_ids_2);

	race_state(car_ids, length);
	race_state(car_ids_2, length_2);
	race_state(car_ids, length);
	race_state(car_ids_2, length_2);
	race_state(car_ids, length);
	race_state(car_ids, length);
	race_state(car_ids_2, length_2);

	return 0;
}
