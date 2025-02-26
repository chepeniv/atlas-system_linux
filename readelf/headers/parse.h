#ifndef _PARSE_
#define _PARSE_

int is_elf(unsigned char *data);
char *parse_arch(unsigned char *data);
char *parse_endianess(unsigned char *data);
char *parse_elf_version(unsigned char *data);

#endif /* _PARSE_ */
