#include <stdlib.h>
#include <string.h>
#include "../headers/parse.h"
#include "../headers/parse_utils.h"
#include "../headers/mem.h"

void *get_bytes(const unsigned char *data, int pos, int incr)
{
	int arch_class = 0x04;
	long *value;

	if (data[arch_class] == ELFCLASS32)
		value = (void *) &data[pos];
	else
		value = (void *) &data[pos + incr]; /* ELFCLASS64 */


	return (value);
}

char *get_hex_str(const unsigned char *data, int pos, int incr, int bytes)
{
	int arch_class = 0x04;
	char *mailback;

	if (data[arch_class] == ELFCLASS32)
		incr = 0;

	mem_alloc((void **) &mailback, sizeof(char), 128);
	for (int b = 0; b < bytes; b++)
		sprintf(&mailback[b * 2], "%02x", data[pos + incr + b]);

	return (mailback);
}

char *create_text__int_str(long value, char *append, int limit)
{
	char *mailback;

	mem_alloc((void **) &mailback, sizeof(char), limit);
	sprintf(mailback, "%ld", value);
	if (append)
		strcat(mailback, append);

	return (mailback);
}

int is_elf(const unsigned char *data)
{
	unsigned char elfmagic[4] = { 0x7f, 0x45, 0x4c, 0x46 };

	for (int i = 0; i < 4; i++)
		if (elfmagic[i] != data[i])
			return (0);

	return (1);
}

int is_arch_32(const unsigned char *data)
{
	if (data[0x04] == 1)
		return (1);

	return (0);
}
