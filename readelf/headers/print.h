#ifndef _PRINT_
#define _PRINT_

int print_hex(unsigned char *data, int size);
char *get_hex_str(const unsigned char *data, int pos, int incr, int bytes);
char *create_text__int_str(long value, char *append, int limit);
char *make_uint16_text(
	const unsigned char *data, int pos, int incr, char *append);

void print_extracted_hex(
	const unsigned char *data,
	int pos, int incr, int bytes);

#endif /* _PRINT_ */
