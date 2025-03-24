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

#define CLASS32 1
#define CLASS64 2

typedef union
{
	unsigned char *raw;
	Elf32_Ehdr    *arch32;
	Elf64_Ehdr    *arch64;
} Ehdr;

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

int is_straight(unsigned char *elf_raw)
{
	switch (elf_raw[EI_DATA])
	{
		case ELFDATA2LSB:
			return (1);
		default:
			return (0);
	}
}

void print_section_header_data(Ehdr elfhdr)
{
	int arch;
	long sect_offset;

	if (!is_straight(elfhdr.raw))
	{
		printf("skipping big-endian order file\n");
		return;
	}

	arch = get_arch(elfhdr.raw);
	switch (arch)
	{
		case CLASS32:
			sect_offset = elfhdr.arch32->e_shoff;
			sect_offset = rectify_elfdata(
				elfhdr.raw,
				sect_offset,
				sizeof(Elf32_Off));
			printf("arch32: phoff: %d\n", (int) sect_offset);
			break;
		case CLASS64:
			sect_offset = elfhdr.arch64->e_shoff;
			sect_offset = rectify_elfdata(
				elfhdr.raw,
				sect_offset,
				sizeof(Elf64_Off));
			printf("arch64: phoff: %ld\n", sect_offset);
			break;
	}
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
					print_section_header_data(elfhdr);
					break;
				case 2:
					elfhdr.arch64 = (Elf64_Ehdr *) elf_data;
					print_section_header_data(elfhdr);
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
