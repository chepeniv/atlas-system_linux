#include <stdlib.h>
#include <string.h>
#include "../headers/parse.h"
#include "../headers/parse_utils.h"
#include "../headers/mem.h"

uint64_t bitwise_reverse(uint64_t origin, uint64_t len)
{
	uint64_t l_pos, r_pos, shift, rev = 0;

	for (uint64_t b = 0; b < len / 2u; b++)
	{
		shift = ((len - 1u) - (2u * b)) * 8u;
		r_pos = 0xffu << (b * 8u);
		l_pos = r_pos << shift;
		rev |= (r_pos & origin) << shift;
		rev |= (l_pos & origin) >> shift;
	}

	return (rev);
}

int is_elf(const unsigned char *data)
{
	unsigned char elfmagic[4] = { 0x7f, 0x45, 0x4c, 0x46 };

	for (int i = 0; i < 4; i++)
		if (elfmagic[i] != data[i])
			return (0);

	return (1);
}

int get_endian_shift(const unsigned char *data)
{
	if (data[EI_DATA] == ELFDATA2MSB)
		return (1);
	return (0);
}

void *get_bytes(const unsigned char *data, int pos, int incr, int typesize)
{
	void *value;
	int shift = 0;

	(void) typesize;

	if (data[EI_CLASS] == ELFCLASS32)
		value = (void *) &data[pos];
	else
		value = (void *) &data[pos + incr]; /* ELFCLASS64 */

	return (value);
}

char *make_uint16_text(
const unsigned char *data,
int pos, int incr, char *append)
{
	uint16_t *num;
	char *mailback;

	num = get_bytes(data, pos, incr, sizeof(uint16_t));
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
