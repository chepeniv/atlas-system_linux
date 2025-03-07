#include "../headers/parse.h"
#include "../headers/parse_utils.h"
#include "../headers/mem.h"

char *get_arch(const unsigned char *data)
{
	char *arch, *mailback;

	switch (data[EI_CLASS])
	{
		case (ELFCLASS32):
			arch = "ELF32";
			break;
		case (ELFCLASS64):
			arch = "ELF64";
			break;
		default:
			arch = "invalid";
	}

	mailback = setup_str_mem(arch, 16);

	return (mailback);
}

char *get_endianess(const unsigned char *data)
{
	char *text, *mailback;

	switch (data[EI_DATA]) /* byte index: [5] */
	{
		case (ELFDATA2LSB):
			text = "2's complement, little endian";
			break;
		case (ELFDATA2MSB):
			text = "2's complement, big endian";
			break;
		default:
			text = "unknown";
	}

	mailback = setup_str_mem(text, 64);

	return (mailback);
}

char *get_elf_ver(const unsigned char *data)
{
	char *text, *mailback;

	switch (data[EI_VERSION]) /* byte index: [6] */
	{
		case (EV_CURRENT):
			text = "1 (current)";
			break;
		default:
			text = "invalid";
	}

	mailback = setup_str_mem(text, 16);

	return (mailback);
}

char *get_abi_ver(const unsigned char *data)
{
	/* ABI Version:    0 */
	char *mailback;

	mem_alloc((void **) &mailback, sizeof(char), 8);
	sprintf(mailback, "%d", data[EI_ABIVERSION]);

	return (mailback);
}

char *get_type(const unsigned char *data)
{
	uint16_t *pos, value;
	char *text, *mailback;

	pos = (uint16_t *) &data[0x10];
	value = get_reverse(data, *pos, sizeof(uint16_t));
	switch (value)
	{
		case (ET_NONE):
			text = "No file type";
			break;
		case (ET_REL):
			text = "REL (Relocatable file)";
			break;
		case (ET_EXEC):
			text = "EXEC (Executable file)";
			break;
		case (ET_DYN):
			text = "DYN (Shared object file)";
			break;
		case (ET_CORE):
			text = "Core file";
			break;
		default:
			text = "Unknown";
	}

	mailback = setup_str_mem(text, 64);
	return (mailback);
}
