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
	/* presume the file descriptor will remain the same */
	/* use malloc/realloc to setup a string varible */
	/* READ EXACTLY READ_SIZE BYTES AT A TIME */
	/* read(file_desc, buffer, READ_SIZE); */
	/* if there are no more lines, or an error occurs, return NULL */
	/* remove any trailing newline and terminate with null character */
	return "hello, world";
}
