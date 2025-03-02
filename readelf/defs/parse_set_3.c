#include <stdlib.h>
#include <string.h>
#include "../headers/parse.h"
#include "../headers/parse_utils.h"
#include "../headers/mem.h"
#include "../headers/const.h"

char *get_prog_hdr_size(const unsigned char *data)
{
	uint16_t *size;
	char *mailback;

	size = get_bytes(data, 0x2a, 12);
	mailback = create_text__int_str(*size, " (bytes)", 32);

	return (mailback);
}

char *get_prog_hdr_count(const unsigned char *data)
{
	uint16_t *num;
	char *mailback;

	num = get_bytes(data, 0x2c, 12);
	mailback = create_text__int_str(*num, NULL, 16);

	return (mailback);
}

char *get_sect_hdr_size(const unsigned char *data)
{
	uint16_t *size;
	char *mailback;

	size = get_bytes(data, 0x2e, 12);
	mailback = create_text__int_str(*size, " (bytes)", 16);

	return (mailback);
}

char *get_sect_hdr_count(const unsigned char *data)
{
	uint16_t *num;
	char *mailback;

	num = get_bytes(data, 0x30, 12);
	mailback = create_text__int_str(*num, NULL, 16);

	return (mailback);
}

char *get_sect_hdr_strtable_index(const unsigned char *data)
{
	uint16_t *index;
	char *mailback;

	index = get_bytes(data, 0x32, 12);
	mailback = create_text__int_str(*index, NULL, 16);

	return (mailback);
}
