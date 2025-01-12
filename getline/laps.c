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
int verify_cars(int *racers, int *lap_tracker, size_t number)
{
	int new_racers = 0;

	for (size_t i = 0; i < number; i++)
	{
		int car = racers[i];

		if (lap_tracker[car] == -1)
		{
			printf("Car %d joined the race\n", car);
			lap_tracker[car] = 0;
			new_racers++;
		}
	}
	return new_racers;
}

void increment_laps(int *lap_tracker, int total)
{
	for (int i = 0; i < total; i++)
	{
		if (lap_tracker[i] != -1)
			lap_tracker[i] += 1;
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
	static int total_cars;
	static int lap_progress;
	static int race_in_progress;

	if (!race_in_progress)
	{
		init_array(lap_tracker, MAX_CARS);
		race_in_progress++;
	}

	int new_racers = verify_cars(racers, lap_tracker, number);

	/* NOTE TO SELF: the cars in racers are the ones that get incremented */

	printf("Race state:\n");
	for (int car = 0; car < MAX_CARS; car++)
	{
		int  lap = lap_tracker[car];
		if (lap != -1)
			printf("Car %d [%d laps]\n", car, lap);
	}

	if (new_racers)
	{
		total_cars += new_racers;
		lap_progress = new_racers;
		return;
	}

	lap_progress += number;

	if (lap_progress == total_cars)
	{
		increment_laps(lap_tracker, MAX_CARS);
		lap_progress = 0;
	}
}
