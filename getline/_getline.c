#include <stdlib.h>		/* malloc, realloc, free */
#include <string.h>		/* strcpy, strncpy, strdup, strcat; memset, memcpy */
#include <unistd.h>		/* read, write, size_t */

#include "_getline.h"

/*
 * task 2 - multi-fd
 * handle multiple file descriptors
 * if called with -1, free everything and reset all static variables
 */

int set_line_end(char *buffer, int read_length)
{
	for (int i = 0; i < read_length; i++)
	{
		if (buffer[i] == '\n')
		{
			buffer[i] = '\0';
			return (i);
		}
	}
	return (read_length);
}

/**
 * _getline -  copy a READ_SIZE-length line from a given file descriptor in to
 * an internal buffer
 * @file_desc: the file id to reference and read from
 *
 * Return: a pointer to the written buffer or NULL upon eof or error
 */
char *_getline(const int file_desc)
{
	static int start_pos;
	static int end_pos;
	static int read_length;
	static char *file_buffer;
	static char *line_buffer;

	if (read_length == 0)
	{
		file_buffer = malloc(sizeof(char) * READ_SIZE);
		line_buffer = malloc(sizeof(char) * READ_SIZE * 2);
	}

	if (end_pos == 0)
		read_length = read(file_desc, file_buffer, READ_SIZE);

	if (read_length <= 0)
	{
		free(file_buffer);
		free(line_buffer);
		return (NULL);
	}

	end_pos += set_line_end(file_buffer, read_length);

	strncpy(
		&line_buffer[start_pos],
		&file_buffer[start_pos],
		end_pos - start_pos);

	start_pos = end_pos + 1;

	if (start_pos >= read_length)
	{
		start_pos = 0;
		end_pos =0;
	}

	return (strdup(line_buffer));
}
