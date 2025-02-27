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
	(void) data;
	/* OS/ABI:    UNIX - System V */
	return ("os");
}

char *parse_abi_ver(const unsigned char *data)
{
	(void) data;
	/* ABI Version:    0 */
	return ("abi ver");
}

char *parse_type(const unsigned char *data)
{
	(void) data;
	/* Type:    EXEC (Executable file) */
	return ("type");
}

char *parse_machine(const unsigned char *data)
{
	(void) data;
	/* Machine:    Advanced Micro Devices X86-64 */
	return ("mach");
}

char *parse_version(const unsigned char *data)
{
	(void) data;
	/* Version:    0x1 */
	return ("vers");
}

char *parse_entry_addr(const unsigned char *data)
{
	(void) data;
	/* Entry point address:    0x400600 */
	return ("entry addr");
}

char *parse_prog_hdr_offset(const unsigned char *data)
{
	(void) data;
	/* Start of program headers:    64 (bytes into file) */
	return ("start of prog hdrs");
}

char *parse_sect_hdr_offset(const unsigned char *data)
{
	(void) data;
	/* Start of section headers:    6936 (bytes into file) */
	return ("start of sect hdrs");
}

char *parse_flags(const unsigned char *data)
{
	(void) data;
	/* Flags:    0x0 */
	return ("flags");
}

char *parse_elf_hdr_size(const unsigned char *data)
{
	(void) data;
	/* Size of this header:    64 (bytes) */
	return ("size of this hdr");
}

char *parse_prog_hdr_size(const unsigned char *data)
{
	(void) data;
	/* Size of program headers:    56 (bytes) */
	return ("size of prog hdrs");
}

char *parse_prog_hdr_count(const unsigned char *data)
{
	(void) data;
	/* Number of program headers:    9 */
	return ("num of prog hdrs");
}

char *parse_sect_hdr_size(const unsigned char *data)
{
	(void) data;
	/* Size of section headers:    64 (bytes) */
	return ("size of sec hdrs");
}

char *parse_sect_hdr_count(const unsigned char *data)
{
	(void) data;
	/* Number of section headers:    31 */
	return ("num of sec hdrs");
}

char *parse_sect_hdr_strtable_index(const unsigned char *data)
{
	(void) data;
	/* Section header string table index:    28 */
	return ("sec hdr str tbl indx");
}
