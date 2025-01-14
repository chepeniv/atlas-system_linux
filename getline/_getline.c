#include <stdlib.h>	/* malloc, realloc, free */
#include <string.h>	/* strcpy, strncpy, strdup, strcat; memset, memcpy */
#include <unistd.h>	/* read, write, size_t */

#include "_getline.h"

void find_line(
char *file_buffer,
char *line_buffer,
int position[1],
int read_length
)
{
	int line_length = 0;
	int i = 0;

	if (file_buffer[position[0]] == '\n')
		position[0]++;

	i = position[0];

	while (
	file_buffer[i] != '\n' &&
	file_buffer[i] != '\0' &&
	i < (read_length - 1))
		i++;

	line_length = i - position[0];
	line_buffer = realloc(line_buffer, line_length + 1);
	memset(line_buffer, '\0', line_length + 1);

	strncpy(
		line_buffer,
		&file_buffer[position[0]],
		line_length);

	position[0] = i;
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
	static int position[1];
	static int read_length;
	static char *file_buffer;
	char *line_buffer;

	if (read_length == 0)
	{
		position[0] = 0;
		file_buffer = malloc(sizeof(char) * READ_SIZE);
		if (!file_buffer)
			return (NULL);

		memset(file_buffer, '\0', READ_SIZE);
		read_length = read(file_desc, file_buffer, READ_SIZE);

		if (read_length <= 0)
		{
			free(file_buffer);
			return (NULL);
		}
	}

	line_buffer = malloc(sizeof(char));
	find_line(file_buffer, line_buffer, position, read_length);

	if (position[0] == 0)
		read_length = 0;
	if (position[0] >= read_length)
		return (NULL);

	return (line_buffer);
}
