#include "../headers/parse_utils.h"
#include "../headers/parse.h"
#include "../headers/mem.h"

/*
 * //// TEST CASES ////
 * solaris32, sortix32, sparcbigendian32, ubuntu64, jpeg.mod, python.obj
 * libperl.so.5.18, sftp-server, vgpreload_memcheck-x86-linux.so, netbsd32
 */

static encoded_item elf_list_machine[259] = {
	{EM_NONE,        "No machine"},
	{EM_M32,         "AT&T WE 32100"},
	{EM_SPARC,       "Sparc"},
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
	{EM_SPARC32PLUS, "Sparc v8+"},
	{EM_960,         "Intel 80960"},
	{EM_PPC,         "PowerPC"},
	{EM_PPC64,       "PowerPC 64-bit"},
	{EM_S390,        "IBM S390"},
	{EM_SPU,         "IBM SPU/SPC"},
	{EM_X86_64,      "Advanced Micro Devices X86-64"},
	{-1, NULL}
};

static encoded_item elf_list_osabi[256] = {
	{ELFOSABI_SYSV,       "UNIX - System V"},
	{ELFOSABI_HPUX,       "HP-UX"},
	{ELFOSABI_NETBSD,     "UNIX - NetBSD"},
	{ELFOSABI_GNU,        "Object uses GNU ELF extensions"},
	{ELFOSABI_LINUX,      "Compatibility alias"},
	{ELFOSABI_SOLARIS,    "UNIX - Solaris"},
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

char *get_os(const unsigned char *data)
{
	char *mailback, *text = NULL;
	int code = data[EI_OSABI];

	for (int i = 0; elf_list_osabi[i].code > -1; i++)
		if (elf_list_osabi[i].code == code)
			text = elf_list_osabi[i].text;

	mem_alloc((void **) &mailback, 1, 64);
	if (!text)
		sprintf(mailback, "<unknown: %x>", code);
	else
		sprintf(mailback, "%s", text);

	return (mailback);
}

char *get_machine(const unsigned char *data)
{
	char *text = NULL, *mailback;
	uint16_t machine;

	machine = *(uint16_t *) &data[0x12];
	machine = get_reverse(data, machine, sizeof(uint16_t));
	for (int i = 0; elf_list_machine[i].code > -1; i++)
		if (elf_list_machine[i].code == machine)
			text = elf_list_machine[i].text;

	mailback = setup_str_mem(text, 128);

	return (mailback);
}

char *get_version(const unsigned char *data)
{
	char *text, *mailback;
	uint32_t *version;

	version = (uint32_t *) get_bytes(data, 0x14, 0, sizeof(uint32_t));
	switch (*version)
	{
		case (EV_CURRENT):
			text = "0x1";
			break;
		default:
			text = "Invalid";
	}

	mailback = setup_str_mem(text, 16);

	return (mailback);
}
