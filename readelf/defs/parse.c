#include <elf.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/parse.h"

/**
 * is_elf -
 * @data:
 *
 * Return:
 */

int is_elf(const unsigned char *data)
{
	unsigned char elfmagic[4] = { 0x7f, 0x45, 0x4c, 0x46 };

	for (int i = 0; i < 4; i++)
		if (elfmagic[i] != data[i])
			return (0);

	return (1);
}

char *parse_arch(const unsigned char *data)
{
	switch (data[EI_CLASS]) /* byte index: [4] */
	{
		case (ELFCLASS32):
			return ("ELF32");
		case (ELFCLASS64):
			return ("ELF64");
		default:
			return ("invalid");
	}
}

char *parse_endianess(const unsigned char *data)
{
	switch (data[EI_DATA]) /* byte index: [5] */
	{
		case (ELFDATA2LSB):
			return ("2's compliment, little-endian");
		case (ELFDATA2MSB):
			return ("2's compliment, big-endian");
		default:
			return ("unknown");
	}
}

char *parse_elf_version(const unsigned char *data)
{
	switch (data[EI_VERSION]) /* byte index: [6] */
	{
		case (EV_CURRENT):
			return ("1 (current)");
		default:
			return ("invalid");
	}
}
