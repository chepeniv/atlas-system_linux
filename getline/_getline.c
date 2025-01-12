#include <stdlib.h>		/* malloc, realloc, free */
#include <string.h>		/* strcpy, strncpy, strdup, strcat; memset, memcpy */
#include <unistd.h>		/* read, write, size_t */

#include "_getline.h"

/* task 2 - multi-fd
 * handle multiple file descriptors
 * if called with -1, free everything and reset all static variables
 */

/**
 * _getline -  read an entire line from a given file descriptor
 * @file_desc:
 *
 * Return:
 */
char *_getline(const int file_desc)
{
	char *buffer = malloc(sizeof(char) * READ_SIZE);
	int rlength = read(file_desc, buffer, READ_SIZE);

	if(rlength <= 0)
	{
		free(buffer);
		return NULL;
	}

	for (int i = 0; i < READ_SIZE; i++)
	{
		if (buffer[i] == '\0' && buffer[i - 1] == '\n')
		{
			buffer[i - 1] = '\0';
			break;
		}
	}

	return buffer;
}
