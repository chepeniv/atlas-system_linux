#include <unistd.h>    /* close(), read() */
#include <stdio.h>     /* printf(), fopen() */
#include <fcntl.h>     /* open() */
#include <stdlib.h>    /* malloc() */
#include <sys/mman.h>  /* mmap() */
#include <sys/stat.h>  /* file info */
#include <string.h>    /* memcmp */
#include <error.h>
#include <errno.h>
#include <elf.h>
#include "elf_ptr.h"

#define CLASS32 1
#define CLASS64 2

/* typedef union */
/* { */
/* 	unsigned char *raw; */
/* 	Elf32_Shdr    *arch32; */
/* 	Elf64_Shdr    *arch64; */
/* } Sect_Hdr; */
/* typedef union */
/* { */
/* 	unsigned char *raw; */
/* 	Elf32_Ehdr    *arch32; */
/* 	Elf64_Ehdr    *arch64; */
/* } Entry_Hdr; */

uint64_t bitwise_reverse(
uint64_t frwd,
uint64_t len)
{
	uint64_t l_pos, r_pos, shift, rev = 0;

	for (uint64_t b = 0; b < len / 2u; b++)
	{
		shift = ((len - 1u) - (2u * b)) * 8u;
		r_pos = 0xffu << (b * 8u);
		l_pos = r_pos << shift;
		rev |= (r_pos & frwd) << shift;
		rev |= (l_pos & frwd) >> shift;
	}

	return (rev);
}

uint64_t rectify_elfdata(
const unsigned char *elf_raw,
uint64_t             value,
uint64_t             typesize)
{
	uint64_t rev = value;

	if (elf_raw[EI_DATA] == ELFDATA2MSB)
		rev = bitwise_reverse(value, typesize);

	return (rev);
}

int get_arch(unsigned char *elf_raw)
{
	switch (elf_raw[EI_CLASS])
	{
		case ELFCLASS32:
			return (CLASS32);
		case ELFCLASS64:
			return (CLASS64);
		default:
			return (0);
	}
}

int is_elf(unsigned char *elf_entry)
{
	unsigned char elf_valid[] = {ELFMAG0, ELFMAG1, ELFMAG2, ELFMAG3};

	if (memcmp(elf_entry, elf_valid, 4) == 0)
		return (get_arch(elf_entry));
	else
		return (0);
}

int is_decr_end(unsigned char *elf_raw)
{
	switch (elf_raw[EI_DATA])
	{
		case ELFDATA2LSB:
			return (1);
		default:
			return (0);
	}
}

void *mmap_file(char *path, int size)
{
	int fd;
	void *elf_data;

	fd = open(path, O_RDONLY);
	elf_data = mmap(
		NULL, size,
		PROT_READ, MAP_PRIVATE,
		fd, 0);
	close(fd);

	return (elf_data);
}

Elf64_Ehdr *get_elf_hdr(void *elf_data)
{
	Elf64_Ehdr *elfhdr = NULL;
	unsigned char *elf_entry;

	elf_entry = (unsigned char *) elf_data;

	if (is_elf(elf_entry))
		elfhdr = (Elf64_Ehdr *) elf_data;

	return (elfhdr);
}

void print_symb(char *str_tbl, Elf64_Sym *sym_tbl)
{
	char *str = str_tbl + sym_tbl->st_name;
	/* char *str = SYMB_STR(str_tbl, sym_tbl); */

	if (strcmp(str, ""))
	{
		if (sym_tbl->st_value)
			printf("%016lx %d %s\n",
				sym_tbl->st_value,
				sym_tbl->st_info,
				str);
		else
			printf("%16c %d %s\n",
				' ',
				sym_tbl->st_info,
				str);
	}
}

Elf64_Shdr *get_sym_sect(Elf64_Shdr *root_sect, uint64_t count )
{
	Elf64_Shdr *sym_sect = NULL;

	for (uint64_t i = 0; i < count; i++)
	{
		if ((root_sect + i)->sh_type == SHT_SYMTAB)
		{
			sym_sect = root_sect + i;
			break;
		}
	}

	return (sym_sect);
}

void iterate_over_symbols(
Elf64_Shdr *sym_sect,
Elf64_Sym  *sym_tbl,
char       *str_tbl)
{
	uint64_t symb_count;

	symb_count = sym_sect->sh_size / sizeof(Elf64_Sym);

	for (uint64_t s = 0; s < symb_count; s++)
		print_symb(str_tbl, sym_tbl + s);
}

void process_symbols(Elf64_Ehdr *elf_hdr)
{
	Elf64_Shdr *root_sect;
	Elf64_Shdr *sym_sect;
	Elf64_Sym  *sym_tbl;
	char       *str_tbl;

	root_sect = (Elf64_Shdr *) SECT_HDR(elf_hdr);
	sym_sect  =  get_sym_sect(root_sect, elf_hdr->e_shnum);
	sym_tbl   = (Elf64_Sym *) SECT(elf_hdr, sym_sect);
	str_tbl   =  STR_TBL(elf_hdr, root_sect, sym_sect);

	iterate_over_symbols(sym_sect, sym_tbl, str_tbl);
}

int main(int count, char **args)
{
	int size;
	void *elf_data;
	struct stat elf_info;
	Elf64_Ehdr *elfhdr;

	for (int i = 1; i < count; i++)
	{
		if (stat(args[i], &elf_info) < 0)
		{
			error(0, 0, "'%s': No such file", args[i]);
		}
		else if (S_ISREG(elf_info.st_mode) && elf_info.st_size)
		{
			size     = elf_info.st_size;
			elf_data = mmap_file(args[i], size);
			elfhdr   = get_elf_hdr(elf_data);
			if (!elfhdr)
				error(0, 0, "%s: file format not recognized ", args[i]);
			else
			{
				process_symbols(elfhdr);
			}

			munmap(elf_data, size);
		}
		else if S_ISDIR(elf_info.st_mode)
		{
			error(0, 0, "Warning: '%s' is a directory", args[i]);
		}
	}

	return (0);
}
