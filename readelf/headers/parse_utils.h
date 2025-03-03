#ifndef _PARSE_UTILS_
#define _PARSE_UTILS_

#include <stdint.h>
#include <elf.h>

typedef unsigned long ulong;

int is_elf(const unsigned char *data);
uint64_t *get_bytes(
	const unsigned char *data, int pos, int incr, int typesize);
uint64_t get_reverse(
	const unsigned char *data, uint64_t value, uint64_t typesize);
Elf64_Off get_hdr_offset(
	const unsigned char *data, uint16_t pos, uint16_t incr);

#endif /* _PARSE_UTILS_ */
