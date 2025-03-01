#include <elf.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <limits.h>
#include "../headers/parse.h"
#include "../headers/mem.h"
#include "../headers/const.h"

encoded_item elf_list_machine[259] = {
	{EM_NONE,        "No machine"},
	{EM_M32,         "AT&T WE 32100"},
	{EM_SPARC,       "SUN SPARC"},
	{EM_386,         "Intel 80386"},
	{EM_68K,         "Motorola m68k family"},
	{EM_88K,         "Motorola m88k family"},
	{EM_IAMCU,       "Intel MCU"},
	{EM_860,         "Intel 80860"},
	{EM_MIPS,        "MIPS R3000 big-endian"},
	{EM_S370,        "IBM System/370"},
	{EM_MIPS_RS3_LE, "MIPS R3000 little-endian"},
	{EM_PARISC,      "HPPA"},
	{EM_VPP500,      "Fujitsu VPP500"},
	{EM_SPARC32PLUS, "Sun's v8plus"},
	{EM_960,         "Intel 80960"},
	{EM_PPC,         "PowerPC"},
	{EM_PPC64,       "PowerPC 64-bit"},
	{EM_S390,        "IBM S390"},
	{EM_SPU,         "IBM SPU/SPC"},
	{EM_X86_64,      "AMD x86-64 architecture"},
	{-1, NULL}
};

encoded_item elf_list_osabi[256] = {
	{ELFOSABI_SYSV,       "UNIX system V ABI"},
	{ELFOSABI_HPUX,       "HP-UX"},
	{ELFOSABI_NETBSD,     "NetBSD"},
	{ELFOSABI_GNU,        "Object uses GNU ELF extensions"},
	{ELFOSABI_LINUX,      "Compatibility alias"},
	{ELFOSABI_SOLARIS,    "Sun Solaris"},
	{ELFOSABI_AIX,        "IBM AIX"},
	{ELFOSABI_IRIX,       "SGI Irix"},
	{ELFOSABI_FREEBSD,    "FreeBSD"},
	{ELFOSABI_TRU64,      "Compaq TRU64 UNIX"},
	{ELFOSABI_MODESTO,    "Novell Modesto"},
	{ELFOSABI_OPENBSD,    "OpenBSD"},
	{ELFOSABI_ARM_AEABI,  "ARM EABI"},
	{ELFOSABI_ARM,        "ARM"},
	{ELFOSABI_STANDALONE, "Standalone (embedded) application"},
	{-1, NULL}
};

long _get_bytes(const unsigned char *data, int pos, int incr)
{
	int arch_class = 0x04;
	long *value;

	if (data[arch_class] == ELFCLASS32)
		value = (long *) &data[pos];
	else
		value = (long *) &data[pos + incr]; /* ELFCLASS64 */


	return (*value);
}

char *_get_hex_str(const unsigned char *data, int pos, int incr, int bytes)
{
	int arch_class = 0x04;
	char *mailback;

	if (data[arch_class] == ELFCLASS32)
		incr = 0;

	mem_alloc((void **) &mailback, BYTES, 128);
	for (int b = 0; b < bytes; b++ )
		sprintf(&mailback[b * 2], "%02x", data[pos + incr + b]);

	return (mailback);
}

void print_extracted_hex(const unsigned char *data, int pos, int incr, int bytes)
{
	char *test;

	test = _get_hex_str(data, pos, incr, bytes);
	printf("hex data extracted: %s\n", test);
	free(test);
}

static char *create_text__int_str(long value, char *append, int limit)
{
	char *mailback;

	mem_alloc((void **) &mailback, BYTES, limit);
	sprintf(mailback, "%ld", value);
	if (append)
		strcat(mailback, append);

	return (mailback);
}

int is_elf(const unsigned char *data)
{
	unsigned char elfmagic[4] = { 0x7f, 0x45, 0x4c, 0x46 };

	for (int i = 0; i < 4; i++)
		if (elfmagic[i] != data[i])
			return (0);

	return (1);
}

char *get_arch(const unsigned char *data)
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

char *get_endianess(const unsigned char *data)
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

char *get_elf_ver(const unsigned char *data)
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

char *get_os(const unsigned char *data)
{
	static char *text = NULL;
	int code = data[EI_OSABI];

	for (int i = 0; elf_list_osabi[i].code > -1; i++)
		if (elf_list_osabi[i].code == code)
			text = elf_list_osabi[i].text;

	return (text);
}

char *make_abi_ver(const unsigned char *data)
{
	/* ABI Version:    0 */
	char *mailback;

	mem_alloc((void **) &mailback, BYTES, 4);
	sprintf(mailback, "%d", data[EI_ABIVERSION]);

	return (mailback);
}

char *get_type(const unsigned char *data)
{
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

char *get_machine(const unsigned char *data)
{
	static char *text = NULL;
	int machine = data[0x12];

	for (int i = 0; elf_list_machine[i].code > -1; i++)
		if (elf_list_machine[i].code == machine)
			text = elf_list_machine[i].text;

	return (text);
}

char *get_version(const unsigned char *data)
{
	uint32_t version;

	/* Version:    0x1 */
	version = data[0x14];
	switch (version)
	{
		case (EV_CURRENT):
			return ("0x1");
		default:
			return ("Invalid");
	}
}

char *make_entry_addr(const unsigned char *data)
{
	/* ElfN_Addr e_entry; */
	char *mailback;
	long int *entry, entry32;

	entry32 = data[0x18];
	if (data[0x04] == ELFCLASS32)
		entry = (long int *) &entry32;
	else
		entry = (long int *) &data[0x18];

	mem_alloc((void **) &mailback, BYTES, 16);
	sprintf(mailback, "%#lx", *entry);

	return (mailback);
}

char *make_prog_hdr_offset(const unsigned char *data)
{
	/* ElfN_Off e_phoff; */
	long int *offset, offset32;
	char *mailback;

	if (data[0x04] == ELFCLASS32)
	{
		offset32 = data[0x1c];
		offset = (long int *) offset32;
	}
	else
	{   /* ELFCLASS64 */
		offset = (long int *) &data[0x20];
	}

	mailback = create_text__int_str(*offset, " (bytes into file)", 64);

	return (mailback);
}

char *make_sect_hdr_offset(const unsigned char *data)
{
	/* /1* ElfN_Off e_shoff; *1/ */
	long int *offset, offset32;
	char *mailback;
	int pos = 0x20;

	if (data[0x04] == ELFCLASS32)
	{
		offset32 = data[pos];
		offset = (long int *) offset32;
	}
	else
	{   /* ELFCLASS64 */
		offset = (long int *) &data[pos + 8];
	}

	mailback = create_text__int_str(*offset, " (bytes into file)", 64);

	return (mailback);
}

char *make_flags(const unsigned char *data)
{
	uint32_t flags;
	char *mailback;

	flags = _get_bytes(data, 0x24, 6);

	mem_alloc((void **) &mailback, BYTES, 8);
	if (flags)
		sprintf(mailback, "%#x", flags);
	else
		sprintf(mailback, "0x0");

	return (mailback);
}

char *parse_elf_hdr_size(const unsigned char *data)
{
	uint16_t size;
	char *mailback;

	size = _get_bytes(data, 0x28, 12);
	mailback = create_text__int_str(size, " (bytes)", 32);

	return (mailback);
}

char *parse_prog_hdr_size(const unsigned char *data)
{
	uint16_t size;
	char *mailback;

	size = _get_bytes(data, 0x2a, 12);
	mailback = create_text__int_str(size, " (bytes)", 32);

	return (mailback);
}

char *parse_prog_hdr_count(const unsigned char *data)
{
	uint16_t num;
	char *mailback;

	num = _get_bytes(data, 0x2c, 12);
	mailback = create_text__int_str(num, NULL, 16);

	return (mailback);
}

char *parse_sect_hdr_size(const unsigned char *data)
{
	uint16_t size;
	char *mailback;

	size = _get_bytes(data, 0x2e, 12);
	mailback = create_text__int_str(size, " (bytes)", 16);

	return (mailback);
}

char *parse_sect_hdr_count(const unsigned char *data)
{
	uint16_t num;
	char *mailback;

	num = _get_bytes(data, 0x30, 12);
	mailback = create_text__int_str(num, NULL, 16);

	return (mailback);
}

char *parse_sect_hdr_strtable_index(const unsigned char *data)
{
	uint16_t index;
	char *mailback;

	index = _get_bytes(data, 0x32, 12);
	mailback = create_text__int_str(index, NULL, 16);

	return (mailback);
}
