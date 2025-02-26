#include "../headers/print.h"
#include <stdio.h>

int print_hex(unsigned char *data, int len)
{
	for (int l = 0; l < len; l += 16)
	{
		for (int p = 0 + l ; p < 16 + l; p += 4)
			printf("%02x%02x%02x%02x ", /* %c%c%c%c works too */
					data[p], data[p + 1], data[p + 2], data[p + 3]);
		putchar('\n');
	}

	return (len);
}
