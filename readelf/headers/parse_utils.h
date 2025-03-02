#ifndef _PARSE_UTILS_
#define _PARSE_UTILS_

int is_elf(const unsigned char *data);
int is_arch_32(const unsigned char *data);
void *get_bytes(const unsigned char *data, int pos, int incr);
char *get_hex_str(const unsigned char *data, int pos, int incr, int bytes);
char *create_text__int_str(long value, char *append, int limit);

#endif /* _PARSE_UTILS_ */
