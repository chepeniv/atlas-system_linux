#ifndef _ELF_PTR_
#define _ELF_PTR_

#include <elf.h>
#include <stdint.h>

/******** COUNTERS ********/

#define SEC_COUNT(elf_hdr) \
	((elf_hdr)->e_shnum)

/* typecast to either (uint64_t *) or (uint32_t *) */
#define SYM_COUNT(sect_hdr) \
	((uint64_t) (sect_hdr)->sh_size / sizeof(Elf64_Sym))

/******** ELF POINTER ARITMETIC ********/

/* typecast ptr and increment by incr */
#define INCR_PTR(ptr, incr) \
	((char *) (ptr) + (incr))

/* get the first section header */
#define SECT_HDR(elf_hdr) \
	INCR_PTR((elf_hdr), (elf_hdr)->e_shoff)

/* find the section referred to by sect_hdr */
#define SECT(elf_hdr, sect_hdr) \
	INCR_PTR((elf_hdr), (sect_hdr)->sh_offset)

/* go to string table section and typecast it to char * */
#define STR_TBL(elf_hdr, sect_hdr, sym_sect_hdr) \
	(char *) SECT((elf_hdr), (sect_hdr) + (sym_sect_hdr)->sh_link)

#endif /* _ELF_PTR_ */
