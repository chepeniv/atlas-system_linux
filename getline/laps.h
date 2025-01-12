#ifndef _LAPS_
#define _LAPS_

#define LENGTH_OF(arr) sizeof(arr) / sizeof(*arr)
#define MAX_CARS 128

#include <unistd.h>		/* read, write, size_t */

int verify_cars(int *racers, int *lap_tracker, size_t number);
void increment_laps(int *tracker, int total);
void init_array(int *zero_array, size_t length);
void race_state(int *racers, size_t number_of);

#endif // _LAPS_
