#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <elf.h>
#include "../headers/parse.h"
#include "../headers/data.h"
#include "../headers/mem.h"
#include "../headers/magic.h"

static int longest_line(char **series)
{
	int longest = 0;
	int len;

	for (int i = 0; series[i]; i++)
	{
		len = strlen(series[i]);
		if (len > longest)
			longest = len;
	}

	return (len);
}

static int count_fields(char **fields)
{
	int num = 0;

	while (fields[num])
		num++;

	return (num);
}

char **get_fields(void)
{
	static char *header_fields[] = {
		"Magic:",
		"Class:",
		"Data:",
		"Version:",
		"OS/ABI:",
		"ABI Version:",
		"Type:",
		"Machine:",
		"Version:",
		"Entry point address:",
		"Start of program headers:",
		"Start of section headers:",
		"Flags:",
		"Size of this header:",
		"Size of program headers:",
		"Number of program headers:",
		"Size of section headers:",
		"Number of section headers:",
		"Section header string table index:",
		NULL
	};

	return (header_fields);
}

int print_data(char **fields, char **entries)
{
	int width = longest_line(fields);

	printf("ELF Header:\n");
	printf("  %s   %s\n", fields[0], entries[0]);
	for (int i = 1; fields[i]; i++)
		if (entries[i])
			printf("  %-*s %s\n", width, fields[i], entries[i]);

	return (0);
}

/*
 * //// OUTPUT ////
 * File: filename (if more than one filename given)
 * ELF Header:
 *   Magic:   7f 45 4c 46 02 01 01 00 00 00 00 00 00 00 00 00
 *   Class:                             ELF64
 *   Data:                              2's complement, little endian
 *   Version:                           1 (current)
 *   OS/ABI:                            UNIX - System V
 *   ABI Version:                       0
 *   Type:                              EXEC (Executable file)
 *   Machine:                           Advanced Micro Devices X86-64
 *   Version:                           0x1
 *   Entry point address:               0x400600
 *   Start of program headers:          64 (bytes into file)
 *   Start of section headers:          6936 (bytes into file)
 *   Flags:                             0x0
 *   Size of this header:               64 (bytes)
 *   Size of program headers:           56 (bytes)
 *   Number of program headers:         9
 *   Size of section headers:           64 (bytes)
 *   Number of section headers:         31
 *   Section header string table index: 28
 * (next filename or error message)
 */

int process_header_data(unsigned char *raw)
{
	char **elf_fields, **elf_entries;
	int flen;

	elf_fields = get_fields();
	flen = count_fields(elf_fields) + 1;
	elf_entries = malloc(sizeof(char *) * flen);
	nullify((void **) elf_entries, flen);

	elf_entries[I_MAGIC]          = get_magic(raw);
	elf_entries[I_ARCH]           = get_arch(raw);
	elf_entries[I_ENDIAN]         = get_endianess(raw);
	elf_entries[I_ELF_VER]        = get_elf_ver(raw);
	elf_entries[I_OS]             = get_os(raw);
	elf_entries[I_ABI_VER]        = get_abi_ver(raw);
	elf_entries[I_TYPE]           = get_type(raw);
	elf_entries[I_MACH]           = get_machine(raw);
	elf_entries[I_VER]            = get_version(raw);
	elf_entries[I_ENTRY_ADDR]     = get_entry_addr(raw);
	elf_entries[I_PRG_HDR_OFFSET] = get_prog_hdr_offset(raw);
	elf_entries[I_SEC_HDR_OFFSET] = get_sect_hdr_offset(raw);
	elf_entries[I_FLAGS]          = get_flags(raw);
	elf_entries[I_ELF_HDR_SIZE]   = get_elf_hdr_size(raw);
	elf_entries[I_PRG_HDR_SIZE]   = get_prog_hdr_size(raw);
	elf_entries[I_PRG_HDR_NUM]    = get_prog_hdr_count(raw);
	elf_entries[I_SEC_HDR_SIZE]   = get_sect_hdr_size(raw);
	elf_entries[I_SEC_HDR_NUM]    = get_sect_hdr_count(raw);
	elf_entries[I_SEC_STR_TBL]    = get_sect_hdr_strtable_index(raw);

	print_data(elf_fields, elf_entries);
	free_text_array(elf_entries);

	return (0);
}
