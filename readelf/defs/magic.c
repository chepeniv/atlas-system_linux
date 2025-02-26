#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../headers/mem.h"
#include "../headers/const.h"

char *get_magic(unsigned char *data)
{
	char *magic, *hex;
	int len = 16;
	int charlen = (len * 3) + 1;

	mem_alloc((void **)  &magic, BYTES, charlen);
	mem_alloc((void **) &hex, BYTES, 4);

	for (int x = 0; x < len; x++)
	{
		sprintf(hex, "%02x ", data[x]);
		strcat(magic, hex);
	}

	free(hex);

	return (magic);
}
