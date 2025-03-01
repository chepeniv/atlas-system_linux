#include "../headers/parse_utils.h"
#include "../headers/parse.h"
#include "../headers/mem.h"

static encoded_item elf_list_machine[259] = {
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

static encoded_item elf_list_osabi[256] = {
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

char *get_os(const unsigned char *data)
{
	char *text = NULL, *mailback;
	int code = data[EI_OSABI];

	for (int i = 0; elf_list_osabi[i].code > -1; i++)
		if (elf_list_osabi[i].code == code)
			text = elf_list_osabi[i].text;

	mailback = setup_str_mem(text, 128);

	return (mailback);
}

char *get_machine(const unsigned char *data)
{
	char *text = NULL, *mailback;
	int machine = data[0x12];

	for (int i = 0; elf_list_machine[i].code > -1; i++)
		if (elf_list_machine[i].code == machine)
			text = elf_list_machine[i].text;

	mailback = setup_str_mem(text, 128);

	return (mailback);
}

char *get_version(const unsigned char *data)
{
	char *text, *mailback;
	uint32_t version;

	/* Version:    0x1 */
	version = data[0x14];
	switch (version)
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
