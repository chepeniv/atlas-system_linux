#include "../headers/parse.h"
#include "../headers/parse_utils.h"
#include "../headers/mem.h"

char *get_entry_addr(const unsigned char *data)
{
	Elf32_Addr entry32;
	Elf64_Addr entry;
	char *mailback;

	entry32 = data[0x18];
	if (data[0x04] == ELFCLASS32)
		entry = entry32;
	else
		entry = data[0x18];

	mem_alloc((void **) &mailback, sizeof(char), 64);
	sprintf(mailback, "%#lx", entry);

	return (mailback);
}

char *get_prog_hdr_offset(const unsigned char *data)
{
	Elf64_Off offset;
	Elf32_Off offset32;
	char *mailback;

	if (data[0x04] == ELFCLASS32)
	{
		offset32 = data[0x1c];
		offset =  offset32;
	}
	else
	{   /* ELFCLASS64 */
		offset =  data[0x20];
	}

	mailback = create_text__int_str(offset, " (bytes into file)", 64);

	return (mailback);
}

char *get_sect_hdr_offset(const unsigned char *data)
{
	Elf32_Off offset32;
	Elf64_Off offset;
	char *mailback;
	int pos = 0x20;

	if (data[0x04] == ELFCLASS32)
	{
		offset32 = data[pos];
		offset = offset32;
	}
	else
	{   /* ELFCLASS64 */
		offset = data[pos + 8];
	}

	mailback = create_text__int_str(offset, " (bytes into file)", 64);

	return (mailback);
}

char *get_flags(const unsigned char *data)
{
	uint32_t *flags;
	char *mailback;

	flags = get_bytes(data, 0x24, 6);

	mem_alloc((void **) &mailback, sizeof(char), 32);
	if (flags)
		sprintf(mailback, "%#x", *flags);
	else
		sprintf(mailback, "0x0");

	return (mailback);
}

char *get_elf_hdr_size(const unsigned char *data)
{
	uint16_t *size;
	char *mailback;

	size = get_bytes(data, 0x28, 12);
	mailback = create_text__int_str(*size, " (bytes)", 32);

	return (mailback);
}
