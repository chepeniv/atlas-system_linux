#include "../headers/parse.h"
#include "../headers/parse_utils.h"
#include "../headers/text.h"

char *get_prog_hdr_size(const unsigned char *data)
{
	char *mailback = make_uint16_text(data, 0x2a, 12, " (bytes)");

	return (mailback);
}

char *get_prog_hdr_count(const unsigned char *data)
{
	char *mailback = make_uint16_text(data, 0x2c, 12, NULL);

	return (mailback);
}

char *get_sect_hdr_size(const unsigned char *data)
{
	char *mailback = make_uint16_text(data, 0x2e, 12, " (bytes)");

	return (mailback);
}

char *get_sect_hdr_count(const unsigned char *data)
{
	char *mailback = make_uint16_text(data, 0x30, 12, NULL);

	return (mailback);
}

char *get_sect_hdr_strtable_index(const unsigned char *data)
{
	char *mailback = make_uint16_text(data, 0x32, 12, NULL);

	return (mailback);
}
