#ifndef _PARSE_
#define _PARSE_

#include <stdio.h>
#include <elf.h>

#define I_MAGIC          0
#define I_ARCH           1
#define I_ENDIAN         2
#define I_ELF_VER        3
#define I_OS             4
#define I_ABI_VER        5
#define I_TYPE           6
#define I_MACH           7
#define I_VER            8
#define I_ENTRY_ADDR     9
#define I_PRG_HDR_OFFSET 10
#define I_SEC_HDR_OFFSET 11
#define I_FLAGS          12
#define I_ELF_HDR_SIZE   13
#define I_PRG_HDR_SIZE   14
#define I_PRG_HDR_NUM    15
#define I_SEC_HDR_SIZE   16
#define I_SEC_HDR_NUM    17
#define I_SEC_STR_TBL    18

int is_elf(const unsigned char *data);

char *get_arch(const unsigned char *data);
char *get_endianess(const unsigned char *data);
char *get_elf_ver(const unsigned char *data);

char *get_os(const unsigned char *data);
char *get_abi_ver(const unsigned char *data);
char *get_type(const unsigned char *data);
char *get_machine(const unsigned char *data);
char *get_version(const unsigned char *data);

char *get_entry_addr(const unsigned char *data);
char *get_prog_hdr_offset(const unsigned char *data);
char *get_sect_hdr_offset(const unsigned char *data);
char *get_flags(const unsigned char *data);
char *get_elf_hdr_size(const unsigned char *data);

char *get_prog_hdr_size(const unsigned char *data);
char *get_prog_hdr_count(const unsigned char *data);
char *get_sect_hdr_size(const unsigned char *data);
char *get_sect_hdr_count(const unsigned char *data);
char *get_sect_hdr_strtable_index(const unsigned char *data);

typedef struct _encoded_item {
	int code;
	char *text;
} encoded_item;

#endif /* _PARSE_ */
