#include "../headers/text.h"
#include "../headers/mem.h"
#include "../headers/parse_utils.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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

void print_extracted_hex(
const unsigned char *data, int pos, int incr, int bytes)
{
	char *test;

	test = get_hex_str(data, pos, incr, bytes);
	printf("hex data extracted: %s\n", test);
	free(test);
}

char *make_uint16_text(
const unsigned char *data,
int pos, int incr, char *append)
{
	uint16_t *num;
	char *mailback;

	num = (uint16_t *) get_bytes(data, pos, incr, sizeof(uint16_t));
	mailback = create_text__int_str(*num, append, 32);

	return (mailback);
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
