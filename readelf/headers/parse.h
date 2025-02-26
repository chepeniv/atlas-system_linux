#ifndef _PARSE_
#define _PARSE_

int is_elf(const unsigned char *data);
char *parse_arch(const unsigned char *data);
char *parse_endianess(const unsigned char *data);
char *parse_elf_version(const unsigned char *data);

#endif /* _PARSE_ */
