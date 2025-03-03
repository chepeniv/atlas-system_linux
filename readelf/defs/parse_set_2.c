#include "../headers/parse.h"
#include "../headers/parse_utils.h"
#include "../headers/mem.h"
#include "../headers/print.h"

char *get_entry_addr(const unsigned char *data)
{
	Elf32_Addr *entry32;
	Elf64_Addr *entry64;
	Elf64_Addr value;
	char *mailback;
	unsigned int width;

	/* get_hdr_offset not called here since typedefs could be diff */
	if (data[0x04] == ELFCLASS32)
	{
		width = sizeof(Elf32_Addr);
		entry32 = (Elf32_Addr *) &data[0x18];
		value =  *entry32;
	}
	else
	{
		width = sizeof(Elf64_Addr);
		entry64 = (Elf64_Addr *) &data[0x18];
		value = *entry64;
	}
	value = get_reverse(data, value, width);

	mem_alloc((void **) &mailback, sizeof(char), 64);
	sprintf(mailback, "%#lx", value);

	return (mailback);
}

char *get_prog_hdr_offset(const unsigned char *data)
{
	char *mailback;
	Elf64_Off value;
	int pos = 0x1c, incr = 4;

	value = get_hdr_offset(data, pos, incr);
	mailback = create_text__int_str(value, " (bytes into file)", 64);
	return (mailback);
}

char *get_sect_hdr_offset(const unsigned char *data)
{
	char *mailback;
	Elf64_Off value;
	int pos = 0x20, incr = 8;

	value = get_hdr_offset(data, pos, incr);
	mailback = create_text__int_str(value, " (bytes into file)", 64);
	return (mailback);
}

char *get_flags(const unsigned char *data)
{
	uint32_t *flags;
	char *mailback;

	flags = (uint32_t *) get_bytes(data, 0x24, 12, sizeof(uint32_t));
	mem_alloc((void **) &mailback, sizeof(char), 32);

	if (*flags)
		sprintf(mailback, "%#x", *flags);
	else
		sprintf(mailback, "0x0");

	return (mailback);
}

char *get_elf_hdr_size(const unsigned char *data)
{
	char *mailback = make_uint16_text(data, 0x28, 12, " (bytes)");

	return (mailback);
}
