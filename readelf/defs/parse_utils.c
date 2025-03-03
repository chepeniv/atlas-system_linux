#include <string.h>
#include "../headers/parse.h"
#include "../headers/parse_utils.h"
#include "../headers/mem.h"

int is_elf(const unsigned char *data)
{
	unsigned char elfmagic[4] = { 0x7f, 0x45, 0x4c, 0x46 };

	for (int i = 0; i < 4; i++)
		if (elfmagic[i] != data[i])
			return (0);

	return (1);
}

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

uint64_t get_reverse(
const unsigned char *data, uint64_t value, uint64_t typesize)
{
	uint64_t rev = value;

	if (data[EI_DATA] == ELFDATA2MSB)
		rev = bitwise_reverse(value, typesize);

	return (rev);
}

uint64_t *get_bytes(const unsigned char *data, int pos, int incr, int typesize)
{
	uint64_t *loc;
	static uint64_t val;

	if (data[EI_CLASS] == ELFCLASS32)
		loc = (uint64_t *) &data[pos];
	else /* ELFCLASS64 */
		loc = (uint64_t *) &data[pos + incr];

	val = *loc;
	val = get_reverse(data, val, typesize);

	return (&val);
}

Elf64_Off get_hdr_offset(
const unsigned char *data, uint16_t pos, uint16_t incr)
{
	Elf32_Off *offset32;
	Elf64_Off *offset64;
	Elf64_Off value;
	unsigned int width;

	if (data[EI_CLASS] == ELFCLASS32)
	{
		width = sizeof(Elf32_Off);
		offset32 = (Elf32_Off *) &data[pos];
		value = *offset32;
	}
	else /* ELFCLASS64 */
	{
		width = sizeof(Elf64_Off);
		offset64 = (Elf64_Off *) &data[pos + incr];
		value = *offset64;
	}
	value = get_reverse(data, value, width);

	return (value);
}
