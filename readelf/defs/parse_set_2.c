#include "../headers/parse.h"
#include "../headers/parse_utils.h"
#include "../headers/mem.h"

char *get_entry_addr(const unsigned char *data)
{
	/* ElfN_Addr e_entry; */
	char *mailback;
	long int *entry, entry32;

	entry32 = data[0x18];
	if (data[0x04] == ELFCLASS32)
		entry = (long int *) &entry32;
	else
		entry = (long int *) &data[0x18];

	mem_alloc((void **) &mailback, sizeof(char), 64);
	sprintf(mailback, "%#lx", *entry);

	return (mailback);
}

char *get_prog_hdr_offset(const unsigned char *data)
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

char *get_sect_hdr_offset(const unsigned char *data)
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
