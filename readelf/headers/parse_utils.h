#ifndef _PARSE_UTILS_
#define _PARSE_UTILS_

typedef unsigned long ulong;

int is_elf(const unsigned char *data);
void *get_bytes(const unsigned char *data, int pos, int incr, int typesize);
char *get_hex_str(const unsigned char *data, int pos, int incr, int bytes);
char *create_text__int_str(long value, char *append, int limit);
int get_endian_shift(const unsigned char *data);
char *make_uint16_text(
	const unsigned char *data, int pos, int incr, char *append);

#endif /* _PARSE_UTILS_ */
