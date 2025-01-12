#include <stdlib.h>		/* malloc, realloc, free */
#include <string.h>		/* strcpy, strncpy, strdup, strcat; memset, memcpy */
#include <stdio.h>		/* printf */
#include "_getline.h"

/*
 * task 1 :
 *
 * create a function that reads an entire line from a given file descriptor
 * prototype:
 * 		char *_getline(const int fd);
 * wherein fd is the file descriptor to read from
 * return a null-terminated string without a newline character
 * if there are no more lines, or an error occurs, return NULL
 *
 * in _getline.h define the macro READ_SIZE which dictates the number of bytes
 * read each time `read(fd, buffer, READ_SIZE)` is called
 *
 * you must read exactly READ_SIZE bytes at a time; no more, no less
 *
 * the value of READ_SIZE is left to your discretion
 *
 * assume fd will always be the same
 */

/*
 * task 2 - multi-fd
 *
 * handle multiple file descriptors
 *
 * if called with -1, free everything and reset all static variables
 */
