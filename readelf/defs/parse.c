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
	/* Class:    ELF64 */
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
	/* Data:    2's complement, little endian */
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

char *parse_elf_ver(const unsigned char *data)
{
	/* Version:    1 (current) */
	switch (data[EI_VERSION]) /* byte index: [6] */
	{
		case (EV_CURRENT):
			return ("1 (current)");
		default:
			return ("invalid");
	}
}

char *parse_os(const unsigned char *data)
{
	/* OS/ABI:    UNIX - System V */
	return (NULL);
}

char *parse_abi_ver(const unsigned char *data)
{
	/* ABI Version:    0 */
	return (NULL);
}

char *parse_type(const unsigned char *data)
{
	/* Type:    EXEC (Executable file) */
	return (NULL);
}

char *parse_machine(const unsigned char *data)
{
	/* Machine:    Advanced Micro Devices X86-64 */
	return (NULL);
}

char *parse_version(const unsigned char *data)
{
	/* Version:    0x1 */
	return (NULL);
}

char *parse_entry_addr(const unsigned char *data)
{
	/* Entry point address:    0x400600 */
	return (NULL);
}

char *parse_prog_hdr_offset(const unsigned char *data)
{
	/* Start of program headers:    64 (bytes into file) */
	return (NULL);
}

char *parse_sect_hdr_offset(const unsigned char *data)
{
	/* Start of section headers:    6936 (bytes into file) */
	return (NULL);
}

char *parse_flags(const unsigned char *data)
{
	/* Flags:    0x0 */
	return (NULL);
}

char *parse_elf_hdr_size(const unsigned char *data)
{
	/* Size of this header:    64 (bytes) */
	return (NULL);
}

char *parse_prog_hdr_size(const unsigned char *data)
{
	/* Size of program headers:    56 (bytes) */
	return (NULL);
}

char *parse_prog_hdr_count(const unsigned char *data)
{
	/* Number of program headers:    9 */
	return (NULL);
}

char *parse_sect_hdr_size(const unsigned char *data)
{
	/* Size of section headers:    64 (bytes) */
	return (NULL);
}

char *parse_sect_hdr_count(const unsigned char *data)
{
	/* Number of section headers:    31 */
	return (NULL);
}

char *parse_sect_hdr_strtable_index(const unsigned char *data)
{
	/* Section header string table index:    28 */
	return (NULL);
}
