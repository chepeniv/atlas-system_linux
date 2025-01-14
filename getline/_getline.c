#include <stdlib.h>	/* malloc, realloc, free */
#include <string.h>	/* strcpy, strncpy, strdup, strcat; memset, memcpy */
#include <unistd.h>	/* read, write, size_t */

#include <stdio.h>	/* TESTING: getchar, printf */

#include "_getline.h"

int find_line(
char *file_buffer,
char *line_buffer,
int read_length,
int position)
{
	int line_length = 0;
	int i = 0;

	if (file_buffer[position] == '\n')
		position++;
	if (position == read_length - 1)
		return (0);

	i = position;

	while (
	file_buffer[i] != '\n' &&
	file_buffer[i] != '\0' &&
	i < (read_length - 1))
		i++;

	line_length = i - position;

	strncpy(
		line_buffer,
		&file_buffer[position],
		line_length);

	return (i);
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
	static int position;
	static int read_length;
	static char *file_buffer;
	char *line_buffer;

	if (read_length == 0)
	{
		file_buffer = malloc(sizeof(char) * READ_SIZE);
		if (!file_buffer)
			return (NULL);

		/* memset(file_buffer, '\0', READ_SIZE); */
		read_length = read(file_desc, file_buffer, READ_SIZE);

		if (read_length <= 0)
		{
			free(file_buffer);
			return (NULL);
		}
	}

	line_buffer = malloc(sizeof(char) * LINE_SIZE);
	memset(line_buffer, '\0', LINE_SIZE);
	position = find_line(file_buffer, line_buffer, read_length, position);

	if (position == 0)
		read_length = 0;
	if (position >= READ_SIZE)
		return (NULL);

	return (line_buffer);
}
