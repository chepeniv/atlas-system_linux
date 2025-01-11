#include <unistd.h>		/* read, write */
#include <stdlib.h>		/* malloc, realloc, free */
#include <string.h>		/* strcpy, strncpy, strdup, strcat; memset, memcpy */
#include "laps.h"

#define LENGTH_OF(arr) sizeof(arr) / sizeof(*arr)


void race_state(int *racers, size_t number_of){
	if (number_of == 0) {
		/* free any allocated memory */
		return;
	}

	static int lap_tracker[128] = {[0 ... 127] = -1};
	sort_array(racers, number_of);

	printf("Race state:\n");

	for (size_t i = 0; i < number_of; i++)
	{
		int car = racers[i];
		lap_tracker[car] = lap_tracker[car] + 1;
		int lap = lap_tracker[car];
		if (lap == 0 )
			printf("Car %d joined the race\n", car);
		printf( "Car %d [%d laps]\n", car, lap);
	}
}

int main(void) {
	int car_ids[3] = {2, 5, 7};
	int car_ids_2[5] = {10, 4, 3, 11, 5};
	int length = LENGTH_OF(car_ids);
	int length_2 = LENGTH_OF(car_ids_2);

	race_state(car_ids, length);
	race_state(car_ids_2, length_2);
	race_state(car_ids, length);
	race_state(car_ids_2, length_2);
	race_state(car_ids, length);
	race_state(car_ids, length);
	race_state(car_ids, length);
	race_state(car_ids, length);
	race_state(car_ids_2, length_2);
	race_state(car_ids_2, length_2);

	return 0;
}
