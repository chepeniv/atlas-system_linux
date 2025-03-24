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

typedef union
{
	unsigned char *raw;
	Elf32_Ehdr    *arch32;
	Elf64_Ehdr    *arch64;
} Ehdr;

/* uint64_t bitwise_reverse( */
/* uint64_t origin, */
/* uint64_t len) */
/* { */
/* 	uint64_t l_pos, r_pos, shift, rev = 0; */

/* 	for (uint64_t b = 0; b < len / 2u; b++) */
/* 	{ */
/* 		shift = ((len - 1u) - (2u * b)) * 8u; */
/* 		r_pos = 0xffu << (b * 8u); */
/* 		l_pos = r_pos << shift; */
/* 		rev |= (r_pos & origin) << shift; */
/* 		rev |= (l_pos & origin) >> shift; */
/* 	} */

/* 	return (rev); */
/* } */

/* uint64_t get_reverse( */
/* const unsigned char *data, */
/* uint64_t             value, */
/* uint64_t             typesize) */
/* { */
/* 	uint64_t rev = value; */

/* 	if (data[EI_DATA] == ELFDATA2MSB) */
/* 		rev = bitwise_reverse(value, typesize); */

/* 	return (rev); */
/* } */

int get_arch(unsigned char *elf_raw)
{
	switch (elf_raw[EI_CLASS])
	{
		case ELFCLASS32:
			return (1);
		case ELFCLASS64:
			return (2);
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

int main(int count, char **args)
{
	int fd, length;
	void *elf_data; /* *elf_data_cruiser; */
	unsigned char *elf_entry;
	struct stat elf_info;

	for (int i = 1; i < count; i++)
	{
		if (stat(args[i], &elf_info) < 0)
		{
			error(0, 0, "'%s': No such file", args[i]);
		}
		else if (S_ISREG(elf_info.st_mode) && elf_info.st_size)
		{
			length = elf_info.st_size;

			fd = open(args[i], O_RDONLY);
			elf_data = mmap(
				NULL, length,
				PROT_READ, MAP_PRIVATE,
				fd, 0);
			close(fd);

			elf_entry = (unsigned char *) elf_data;
			switch (is_elf(elf_entry))
			{
				Ehdr elfhdr;
				case 1:
					elfhdr.arch32 = (Elf32_Ehdr *) elf_data;
					(void) elfhdr;
					break;
				case 2:
					elfhdr.arch64 = (Elf64_Ehdr *) elf_data;
					(void) elfhdr;
					break;
				default:
					error(0, 0, "%s: file format not recognized ", args[i]);
			}

			munmap(elf_data, length);
		}
		else if S_ISDIR(elf_info.st_mode)
		{
			error(0, 0, "Warning: '%s' is a directory", args[i]);
		}
	}

	return (0);
}
