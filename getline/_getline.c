#include <stdlib.h>	/* malloc, realloc, free */
#include <string.h>	/* strcpy, strncpy, strdup, strcat; memset, memcpy */
#include <unistd.h>	/* read, write, size_t */

#include "_getline.h"

/**
 * get_file_index - returns an index to a data_buffer given a descriptor and an
 * array. if it doesn't exist on the array it will be appended to it
 * @file_chain: the array to examine and operate on
 * @count: the current size of the array
 * @desc: the file id to search for
 *
 * Return: the index at which the array is stored in the array
 */
int get_file_index(data_buffer **file_chain, int *count, int desc)
{
	int index = *count;

	/* search for index of file descriptor */
	for (int i = 0; i < count[0]; i++)
		if ((*file_chain)[i].desc == desc)
			return (i);

	/* file desc not found, append new index */
	*count = *count + 1;
	if (*count == 1)
		*file_chain = malloc(sizeof(data_buffer));
	else
		*file_chain = realloc(*file_chain, sizeof(data_buffer) * (*count));
	(*file_chain)[index].desc = desc;
	(*file_chain)[index].length = -1;
	(*file_chain)[index].position = 0;
	(*file_chain)[index].data = malloc(sizeof(char));

	return (index);
}

/**
 * extract_file_data - completely write the given file's data into a
 * data_buffer
 * @file: a pointer to a data_buffer into which the data is stored
 *
 * Return: void
 */
void extract_file_data(data_buffer **file)
{
	data_buffer *handle = *file;
	char *data_chunk;
	int read_length = 0;

	data_chunk = malloc(sizeof(char) * READ_SIZE);
	if (!data_chunk)
		return;

	/* incrementally build data from given file */
	handle->length = 0;
	do {
		memset(data_chunk, '\0', READ_SIZE);
		read_length = read(handle->desc, data_chunk, READ_SIZE);
		if (read_length > 0)
		{
			handle->data = realloc(
				handle->data,
				handle->length + read_length + 1);
			if (!handle->data)
				break;

			strncpy(&handle->data[handle->length], data_chunk, read_length);
			handle->length += read_length;
		}
	} while (read_length > 0);

	free(data_chunk);
}

/**
 * free_buffers - completely liberates all allocated memory within an array
 * @count: the size of the array
 * @buffers: the double buffered array to clean up
 *
 * Return: if no errors occurs it returns NULL
 */
void *free_buffers(int *count, data_buffer **buffers)
{
	for (int i = 0; i < *count; i++)
		free((*buffers)[i].data);

	free(*buffers);
	*count = 0;

	return (NULL);
}

/**
 * extract_line -
 * @file:
 *
 * Return:
 */
data_buffer extract_line(data_buffer **file)
{
	data_buffer line = { .length = 0, .position = 0, .data = NULL };
	data_buffer *handle = *file;
	char symbol;

	line.position = handle->position;
	if (line.position >= handle->length)
		return (line);

	do {
		symbol = handle->data[line.position++];
	} while (symbol != '\n' && symbol != '\0');

	line.length = line.position - handle->position;
	line.data = malloc(sizeof(char) * (line.length + 1));
	if (!line.data)
		return (line);

	memset(line.data, '\0', line.length + 1);
	strncpy(line.data, &handle->data[handle->position], line.length);

	handle->position = line.position;

	/* replace newline with zero-terminator */
	if (line.data[line.length - 1] == '\n')
		line.data[line.length - 1] = '\0';

	return (line);
}

/**
 * _getline -  extract a line from the given file
 * @desc: the file id to reference
 *
 * Return: a pointer to the line buffer or NULL upon eof or error
 */
char *_getline(const int desc)
{
	static data_buffer *file_chain;
	static int count;
	data_buffer *file;
	data_buffer line;
	int index = 0;

	if (desc < 0)
		return (free_buffers(&count, &file_chain));

	index = get_file_index(&file_chain, &count, desc);
	file = &file_chain[index];
	if (file->length < 0)
		extract_file_data(&file);

	line = extract_line(&file);

	return (line.data);
}
