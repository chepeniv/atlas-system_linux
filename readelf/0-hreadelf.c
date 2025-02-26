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
	if (readlen < 0)
	{
		free(elf_raw);
		err_print(errno, procname, filename);
	}

	if (is_elf(elf_raw))
	{
		/* process raw elf data here */
		print_hex(elf_raw, hlen);
	}
	else
	{
		free(elf_raw);
		err_print(E_NELF, procname, filename);
	}

	free(elf_raw);

	return (EXIT_SUCCESS);
}
