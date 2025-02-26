#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../headers/parse.h"
#include "../headers/data.h"
#include "../headers/mem.h"

/*
 * //// OUTPUT ////
 *
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

	/* handle index 0 special case independently */
	for (int i = 0; fields[i]; i++)
		if (entries[i])
			printf("%-*s %s\n", width, fields[i], entries[i]);

	return (0);
}

/* static */
int count_fields(char **fields)
{
	int num = 0;

	while (fields[num])
		num++;

	return (num);
}

int process_header_data(unsigned char *raw)
{
	char **elf_fields, **elf_entries;
	/* int flen; */

	elf_fields = get_fields();
	/* flen = count_fields(elf_fields); */

	/* elf_entries = malloc(sizeof(char *) * flen); */
	/* nullify((void **) elf_entries, flen); */

	(void) raw;
	(void) elf_entries;

	print_data(elf_fields, elf_fields);

	return (0);
}
