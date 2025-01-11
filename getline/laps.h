#include <stdio.h>

void print_int_array(int * numbers, int length)
{
	int i;

	putchar('[');
	for (i = 0; i < length - 1; i++)
		printf("%d, ", numbers[i]);
	printf("%d", numbers[i]);
	printf("] ");
}

void sort_array(int * arr, size_t length)
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
				arr[pos] = arr[pos + 1] ;
				arr[pos + 1] = hold;
			}
			pos++;
		}
		len--;
		pos = 0;
	}
}
