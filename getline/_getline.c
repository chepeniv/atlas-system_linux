#include <stdlib.h>	/* malloc, realloc, free */
#include <string.h>	/* strcpy, strncpy, strdup, strcat; memset, memcpy */
#include <unistd.h>	/* read, write, size_t */

#include "_getline.h"

/**
 * find_line - from a given buffer copy a single line into another buffer
 * starting from a given position
 * @file_buffer: the source buffer to analyse
 * @line_buffer: the destination buffer to write the extracted line into
 * @position: the position to from which to start reading the source buffer
 * @read_length: the length of the source buffer
 *
 * Return: void, values for line_buffer and position are written directly into
 * their corresponding static buffers
 */
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

	/* dynamically set needed memory */
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
 * _getline -  extract a line from the given file descriptor
 * @file_desc: the file id to parse
 *
 * Return: a pointer to the line buffer or NULL upon eof or error
 */
char *_getline(const int file_desc)
{
	static int read_length;
	static int position[1];
	static char *file_buffer;
	char *line_buffer;

	if (read_length == 0)
	{
		file_buffer = malloc(sizeof(char) * READ_SIZE);
		if (!file_buffer)
			return (NULL);

		read_length = read(file_desc, file_buffer, READ_SIZE);
		if (read_length <= 0)
		{
			free(file_buffer);
			return (NULL);
		}
	}

	/* initialize pointer before passing it along */
	line_buffer = malloc(sizeof(char));
	find_line(file_buffer, line_buffer, position, read_length);

	/* figure out how to handle files larger than READ_SIZE */
	if (position[0] == 0)
		read_length = 0;
	if (position[0] >= read_length)
		return (NULL);

	return (line_buffer);
}
