#include <stdlib.h>
#include <string.h>
#include "../headers/parse.h"

/**
 * is_elf -
 * @data:
 *
 * Return:
 */

int is_elf(unsigned char *data)
{
	unsigned char elfmagic[4] = { 0x7f, 0x45, 0x4c, 0x46 };
	int i;

	for (i = 0; i < 4; i++)
		if (elfmagic[i] != data[i])
			return (0);

	return (1);
}
