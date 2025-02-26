#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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
		"Magic",
		"Class",
		"Data",
		"Version",
		"OS/ABI",
		"ABI Version",
		"Type",
		"Machine",
		"Version",
		"Entry point address",
		"Start of program headers",
		"Start of section headers",
		"Flags",
		"Size of this header",
		"Size of program headers",
		"Number of program headers",
		"Size of section headers",
		"Number of section headers",
		"Section header string table index",
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
			printf("%-*s:\t%s\n", width, fields[i], entries[i]);

	return (0);
}

/* int process_header_data(char *raw) */
/* { */
/* 	char **elf_fields, **elf_entries; */

/* 	elf_fields = get_fields(); */
/* } */
