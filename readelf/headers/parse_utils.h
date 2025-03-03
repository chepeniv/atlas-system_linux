#ifndef _PARSE_UTILS_
#define _PARSE_UTILS_

#include <stdint.h>

typedef unsigned long ulong;

int is_elf(const unsigned char *data);
uint64_t *get_bytes(const unsigned char *data, int pos, int incr, int typesize);
char *get_hex_str(const unsigned char *data, int pos, int incr, int bytes);
char *create_text__int_str(long value, char *append, int limit);
char *make_uint16_text(
	const unsigned char *data, int pos, int incr, char *append);
uint64_t get_reverse(
	const unsigned char *data, uint64_t value, uint64_t typesize);

#endif /* _PARSE_UTILS_ */
