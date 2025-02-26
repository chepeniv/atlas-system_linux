#include "headers/help.h"
#include "headers/str.h"
#include "headers/err.h"
#include "headers/mem.h"
#include "headers/print.h"
#include "headers/const.h"
#include "headers/parse.h"
#include "headers/data.h"
#include <elf.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

/*
 * //// INSTRUCTIONS ////
 *
 * emulate: readelf -W -h
 * usage : ./0-hreadelf elf_flie
 *
 * display information contained in the ELF file header
 * handle various operating systems and architectures
 * stdout, stderr, and status should be exactly the same as /usr/bin/readelf
 * handle 32 and 64 bit
 * handle both LSB and MSB
 * handle all types of ELF files
 *
 * only system (3) and exec* (2/3) not allowed
 */

int main(int c, char **argv)
{
	int readlen, hlen = 64;
	FILE *elf_file;
	char *procname, *filename;
	unsigned char *elf_raw;

	procname = argv[0];
	if (c == 1)
		err_print(W_NOARG, procname, NULL);

	filename = argv[1];
	elf_file = fopen(filename, "rb");
	if (!elf_file)
		err_print(errno, procname, filename);

	mem_alloc((void **) &elf_raw, BYTES, hlen);
	readlen = fread(elf_raw, BYTES, hlen, elf_file);
	fclose(elf_file);
	if (readlen < 0)
	{
		free(elf_raw);
		err_print(errno, procname, filename);
	}

	if (is_elf(elf_raw))
		process_header_data(elf_raw); /* print_hex(elf_raw, hlen); */
	else
	{
		free(elf_raw);
		err_print(E_NELF, procname, filename);
	}

	free(elf_raw);

	return (EXIT_SUCCESS);
}
