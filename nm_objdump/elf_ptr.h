#ifndef _ELF_PTR_
#define _ELF_PTR_

#include <elf.h>
#include <stdint.h>

/******** COUNTERS ********/
/**************************/

/* typecast to (uint64_t *) or (uint32_t *) ? */
#define SEC_COUNT(elf_hdr) \
	((uint64_t) (elf_hdr)->e_shnum)

/* typecast to (uint64_t *) or (uint32_t *) ? */
#define SYM_COUNT(sect_hdr) \
	((uint64_t) (sect_hdr)->sh_size / sizeof(Elf64_Sym))

/******** ELF POINTER ARITMETIC ********/
/***************************************/

#define INCR_PTR(ptr, incr) \
	((char *) (ptr) + (incr))

/* typecast to (Elf64_Shdr *) or (Elf32_Shdr *) */
#define SECT_HDR(elf_hdr) \
	INCR_PTR((elf_hdr), (elf_hdr)->e_shoff)

#define SECT(elf_hdr, sect_hdr) \
	INCR_PTR((elf_hdr), (sect_hdr)->sh_offset)

/* typecast to (Elf64_Sym *) or (Elf32_Sym *)*/
#define SYMB(elf_hdr, sect_hdr) \
	SECT((elf_hdr), (sect_hdr))

#define STR_TBL(elf_hdr, rootsect_hdr, sym_sect_hdr) \
	SECT((elf_hdr), (rootsect_hdr) + (sym_sect_hdr)->sh_link)

#define SYMB_STR(str_tbl, sym_tbl) \
	INCR_PTR((str_tbl), (sym_tbl)->st_name)

#endif /* _ELF_PTR_ */
