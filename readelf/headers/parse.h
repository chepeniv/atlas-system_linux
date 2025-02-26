#ifndef _PARSE_
#define _PARSE_

int is_elf(const unsigned char *data);
char *parse_arch(const unsigned char *data);
char *parse_endianess(const unsigned char *data);
char *parse_elf_ver(const unsigned char *data);
char *parse_os(const unsigned char *data);
char *parse_abi_ver(const unsigned char *data);
char *parse_type(const unsigned char *data);
char *parse_machine(const unsigned char *data);
char *parse_version(const unsigned char *data);
char *parse_entry_addr(const unsigned char *data);
char *parse_prog_hdr_offset(const unsigned char *data);
char *parse_sect_hdr_offset(const unsigned char *data);
char *parse_flags(const unsigned char *data);
char *parse_elf_hdr_size(const unsigned char *data);
char *parse_prog_hdr_size(const unsigned char *data);
char *parse_prog_hdr_count(const unsigned char *data);
char *parse_sect_hdr_size(const unsigned char *data);
char *parse_sect_hdr_count(const unsigned char *data);
char *parse_sect_hdr_strtable_index(const unsigned char *data);

#endif /* _PARSE_ */
