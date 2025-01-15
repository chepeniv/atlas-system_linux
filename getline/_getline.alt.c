#include <stdlib.h>	/* malloc, realloc, free */
#include <string.h>	/* strcpy, strncpy, strdup, strcat; memset, memcpy */
#include <unistd.h>	/* read, write, size_t */

#include "_getline.h"

/**
 * extract_line - read and find a line from a given data buffer
 * @file: the struct containing the source buffer to analyse
 *
 * Return: a data structure containing the extracted line along with some
 * metadata
 */
data_buffer extract_line(data_buffer file)
{
	const char *data = file.data;
	data_buffer line = { .length = 0, .position = 0, .data = NULL };

	/* move pass newline char */
	if (data[file.position] == '\n')
		file.position++;

	/* find end of line */
	line.position = file.position;
	while (
	data[line.position] != '\n' &&
	data[line.position] != '\0' &&
	line.position < (file.length - 1))
		line.position++;

	/* allocate needed memory for line data */
	line.length = line.position - file.position;
	line.data = malloc(sizeof(char) * (line.length + 1));
	memset(line.data, '\0', line.length + 1);

	/* copy line data from file_buffer into line_buffer */
	strncpy(
		line.data,
		&data[file.position],
		line.length);

	/* advance position to next line*/
	return (line);
}

/**
 * extract_file_data - read all the data in a given file and store it in a
 * buffer
 * @file_desc: the file's reference id
 * @file: the data structure containing the buffer to write to
 *
 * Return: returns a struct containing the data extracted as well as relevant
 * metadata needed to properly process it
 */
data_buffer extract_file_data(int file_desc, data_buffer file)
{
	char *data_buffer = malloc(sizeof(char) * READ_SIZE);
	int read_length = 0;

	file.data = malloc(sizeof(char));
	file.length = 0;

	/* incrementally extract all data from given file */
	do {
		memset(data_buffer, '\0', READ_SIZE);
		read_length = read(file_desc, data_buffer, READ_SIZE);

		if (read_length > 0)
		{
			file.data = realloc(file.data, file.length + read_length + 1);

			/* append new data to data recorded */
			strncpy(
				&file.data[file.length],
				data_buffer,
				read_length);

			file.length += read_length;
		}
	} while (read_length);

	free(data_buffer);

	return (file);
}

/**
 * _getline -  extract a line from the given file
 * @file_desc: the file id to reference
 *
 * Return: a pointer to the line buffer or NULL upon eof or error
 */
char *_getline(const int file_desc)
{
	static data_buffer file = { .length = -1, .position = 0, .data = NULL };
	data_buffer line;

	if (file.length < 0)
		file = extract_file_data(file_desc, file);

	line = extract_line(file);

	/* terminate */
	file.position = line.position;
	if (file.position >= file.length)
	{
		free(file.data);
		free(line.data);
		return (NULL);
	}

	return (line.data);
}
