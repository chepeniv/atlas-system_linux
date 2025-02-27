#include <elf.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "../headers/parse.h"
#include "../headers/mem.h"
#include "../headers/const.h"

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
	switch (data[EI_OSABI])
	{
		case (ELFOSABI_SYSV):
			return ("UNIX System V ABI");
		case (ELFOSABI_HPUX):
			return ("HP-UX ABI");
		case (ELFOSABI_NETBSD):
			return ("NetBSD ABI");
		case (ELFOSABI_LINUX):
			return ("Linux ABI");
		case (ELFOSABI_SOLARIS):
			return ("Solaris ABI");
		case (ELFOSABI_IRIX):
			return ("IRIX ABI");
		case (ELFOSABI_FREEBSD):
			return ("FreeBSD ABI");
		case (ELFOSABI_TRU64):
			return ("TRU64 UNIX ABI");
		case (ELFOSABI_ARM):
			return ("ARM architecture ABI");
		case (ELFOSABI_STANDALONE):
			return ("Stand-alone (embedded) ABI");
		default:
			return ("UNIX System V ABI");
	}
}

char *parse_abi_ver(const unsigned char *data)
{
	/* ABI Version:    0 */
	char *mailback;

	mem_alloc((void **) &mailback, BYTES, 4);
	sprintf(mailback, "%d", data[EI_ABIVERSION]);

	return (mailback);
}

char *parse_type(const unsigned char *data)
{
	/* Type:    EXEC (Executable file) */
	uint16_t type;

	type = data[0x10];
	switch (type)
	{
		case (ET_REL):
			return ("");
		case (ET_EXEC):
			return ("EXEC (Executable file)");
		case (ET_DYN):
			return ("DYN (Position-Independent Executable file)");
		case (ET_CORE):
			return ("");
		default:
			return ("Unknown");
	}
}

char *parse_machine(const unsigned char *data)
{
	/* Machine:    Advanced Micro Devices X86-64 */
	uint16_t machine;

	machine = data[0x12];
	switch (machine)
	{
		case (EM_M32):
			return ("AT&T WE 32100");
		case (EM_SPARC):
			return ("AT&T WE 32100");
		case (EM_386):
			return ("AT&T WE 32100");
		case (EM_68K):
			return ("Motorola 68000");
		case (EM_88K):
			return ("Motorola 88000");
		case (EM_860):
			return ("Intel 80860");
		case (EM_MIPS):
			return ("MIPS RS3000 (big-endian only)");
		case (EM_PARISC):
			return ("HP/PA");
		case (EM_SPARC32PLUS):
			return ("SPARC with enhanced instruction set");
		case (EM_PPC):
			return ("PowerPC");
		case (EM_PPC64):
			return ("PowerPC 64-bit");
		case (EM_S390):
			return ("IBM S/390");
		case (EM_ARM):
			return ("Advanced RISC Machines");
		case (EM_SH):
			return ("Renesas SuperH");
		case (EM_SPARCV9):
			return ("SPARC v9 64-bit");
		case (EM_IA_64):
			return ("Intel Itanium");
		case (EM_X86_64):
			return ("AMD x86-64");
		case (EM_VAX):
			return ("DEC Vax");
		default:
			return ("Unknown");
	}
}

char *parse_version(const unsigned char *data)
{
	(void) data;
	/* uint32_t e_version; */
	/* Version:    0x1 */
	return ("vers");
}

char *parse_entry_addr(const unsigned char *data)
{
	(void) data;
	/* ElfN_Addr e_entry; */
	/* Entry point address:    0x400600 */
	return ("entry addr");
}

char *parse_prog_hdr_offset(const unsigned char *data)
{
	(void) data;
	/* ElfN_Off e_phoff; */
	/* Start of program headers:    64 (bytes into file) */
	return ("start of prog hdrs");
}

char *parse_sect_hdr_offset(const unsigned char *data)
{
	(void) data;
	/* ElfN_Off e_shoff; */
	/* Start of section headers:    6936 (bytes into file) */
	return ("start of sect hdrs");
}

char *parse_flags(const unsigned char *data)
{
	(void) data;
	/* uint32_t e_flags; */
	/* Flags:    0x0 */
	return ("flags");
}

char *parse_elf_hdr_size(const unsigned char *data)
{
	(void) data;
	/* uint16_t e_ehsize; */
	/* Size of this header:    64 (bytes) */
	return ("size of this hdr");
}

char *parse_prog_hdr_size(const unsigned char *data)
{
	(void) data;
	/* uint16_t e_phentsize; */
	/* Size of program headers:    56 (bytes) */
	return ("size of prog hdrs");
}

char *parse_prog_hdr_count(const unsigned char *data)
{
	(void) data;
	/* uint16_t e_phnum; */
	/* Number of program headers:    9 */
	return ("num of prog hdrs");
}

char *parse_sect_hdr_size(const unsigned char *data)
{
	(void) data;
	/* uint16_t e_shentsize; */
	/* Size of section headers:    64 (bytes) */
	return ("size of sec hdrs");
}

char *parse_sect_hdr_count(const unsigned char *data)
{
	(void) data;
	/* uint16_t e_shnum; */
	/* Number of section headers:    31 */
	return ("num of sec hdrs");
}

char *parse_sect_hdr_strtable_index(const unsigned char *data)
{
	(void) data;
	/* uint16_t e_shstrndx; */
	/* Section header string table index:    28 */
	return ("sec hdr str tbl indx");
}
