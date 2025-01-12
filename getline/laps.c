#include <stdlib.h>		/* malloc, realloc, free */
#include <string.h>		/* strcpy, strncpy, strdup, strcat; memset, memcpy */
#include <stdio.h>		/* printf */
#include "laps.h"

/**
 * init_array - initializes every value in a given array to -1
 * @zero_array: array to operate on
 * @length: number of elements in given array
 *
 * Return: void - since the array is operated on directly, there's no need to
 * return any new construction
 */
void init_array(int *zero_array, size_t length)
{
	for (size_t i = 0; i < length; i++)
		zero_array[i] = -1;
}

/**
 * verify_cars -
 * @racers:
 * @lap_tracker:
 * @number:
 *
 * Return: number of new cars joining the race
 */
void verify_cars(int *racers, int *lap_tracker, size_t number)
{
	for (size_t i = 0; i < number; i++)
	{
		int car = racers[i];

		if (lap_tracker[car] == -1)
			printf("Car %d joined the race\n", car);
	}
}

/**
 * race_state -
 * @racers:
 * @number:
 *
 * Return:
 */
void race_state(int *racers, size_t number)
{
	if (number == 0)
		return;

	static int lap_tracker[MAX_CARS];
	static int race_in_progress;

	if (!race_in_progress)
	{
		init_array(lap_tracker, MAX_CARS);
		race_in_progress++;
	}

	verify_cars(racers, lap_tracker, number);

	for (size_t i = 0; i < number; i++)
	{
		int car = racers[i];
		lap_tracker[car] += 1;
	}

	printf("Race state:\n");
	for (int car = 0; car < MAX_CARS; car++)
	{
		int  lap = lap_tracker[car];
		if (lap != -1)
			printf("Car %d [%d laps]\n", car, lap);
	}
}
