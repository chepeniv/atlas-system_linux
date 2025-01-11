#include <stdlib.h>		/* malloc, realloc, free */
#include <string.h>		/* strcpy, strncpy, strdup, strcat; memset, memcpy */
#include <stdio.h>		/* printf */
#include "laps.h"

void init_array(int *zero_array, size_t length)
{
	if (zero_array[0] == -1)
		return;

	for (size_t i = 0; i < length; i++)
		zero_array[i] = -1;
}

void sort_array(int *arr, size_t length)
{
	size_t len = length, pos = 0;
	int hold;

	while (len != 0)
	{
		while (pos + 1 < len)
		{
			if (arr[pos] > arr[pos + 1])
			{
				hold = arr[pos];
				arr[pos] = arr[pos + 1];
				arr[pos + 1] = hold;
			}
			pos++;
		}
		len--;
		pos = 0;
	}
}

void check_participation(int *racers, int *lap_tracker, size_t number)
{
	for (size_t i = 0; i < number; i++)
	{
		int car = racers[i];

		if (lap_tracker[car] == -1)
			printf("Car %d joined the race\n", car);
	}
}

void race_state(int *racers, size_t number_of)
{
	if (number_of == 0)
		return;

	static int lap_tracker[MAX_CARS];

	init_array(lap_tracker, MAX_CARS);

	check_participation(racers, lap_tracker, number_of);
	sort_array(racers, number_of);

	printf("Race state:\n");
	for (size_t i = 0; i < number_of; i++)
	{
		int car = racers[i];

		lap_tracker[car] = lap_tracker[car] + 1;

		int lap = lap_tracker[car];

		printf("Car %d [%d laps]\n", car, lap);
	}
}
