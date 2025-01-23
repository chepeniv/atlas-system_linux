#include "hls.h"

char *process_time(time_t time)
{
	int end = 0;
	char *read_time = ctime(&time);

	while (read_time[end] != '\n')
		end++;
	read_time[end - 8] = '\0'; /* remove milliseconds and year */

	return (&read_time[4]); /* remove day of the week */
}
