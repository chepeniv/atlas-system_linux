#include "headers/help.h"
#include "headers/str.h"
#include "headers/err.h"
#include "headers/mem.h"
#include "headers/print.h"
#include "headers/const.h"
#include <elf.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>


/* only system (3) and exec* (2/3) not allowed */

/*
 * //// INSTRUCTIONS ////
 *
 * emulate: readelf -W -h
 * usage : ./0-hreadelf elf_flie
 *
 * display information contained in the ELF file header
 * handle various operating systems and architectures
 * stdout, stderr, and status should be exactly the same
 * handle 32 and 64 bit
 * handle both LSB and MSB
 * handle all types of ELF files
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

/*
 * //// PSEUDOCODE ////
 *
 * determine if  file is ELF
 *     otherwise output error
 * determine 32/64
 * determine LSB/MSB
 * determine type of ELF
 * parse header bytes
 * interpret header data
 */

int main(int c, char **argv)
{
	int readlen, hlen = 64;
	FILE *elf_file;
	char *filename;
	unsigned char *elfdata;

	if (c == 1)
	{
		errno = W_NOARG;
		err_print(argv[0], NULL);
	}

	filename = argv[1];
	elf_file = fopen(filename, "rb");
	if (!elf_file)
		err_print(argv[0], filename);

	mem_alloc((void **) &elfdata, BYTES, hlen);
	readlen = fread(elfdata, BYTES, hlen, elf_file);
	if (readlen < 0)
	{
		printf("errno: %d\n", errno); /* debugging output */
		err_print(argv[0], filename);
	}

	print_hex(elfdata, hlen);

	free(elfdata);

	return (EXIT_SUCCESS);
}
