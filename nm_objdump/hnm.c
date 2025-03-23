#include <unistd.h>    /* close(), read() */
#include <stdio.h>     /* printf() */
#include <fcntl.h>     /* open() */
#include <stdlib.h>    /* malloc() */
#include <sys/mman.h>  /* mmap() */
#include <sys/stat.h>  /* file info */

/*
 * NOTES:
 * void *mmap(NULL, len = filesize, PROT_READ, MAP_PRIVATE, fd, offset = 0)
 */

int main(int count, char **arguments)
{
	/* int fd, length = 256; */
	/* unsigned char *elf_file_data; */
	struct stat elf_file_info;

	for (int i = 1; i < count; i++)
	{
		if (stat(arguments[i], &elf_file_info) < 0)
		{
			printf("filename \"%s\" is not valid\n", arguments[i]);
		}
		else if (S_ISREG(elf_file_info.st_mode))
		{
			printf("filename \"%s\" is valid and is of size %ld\n",
				arguments[i],
				elf_file_info.st_size
				);
		}
		else
		{
			printf("filename \"%s\" is not a regular filetype\n", arguments[i]);
		}
	}

	return (0);
}
