#include <stdlib.h>	/* malloc, realloc, free */
#include <string.h>	/* strcpy, strncpy, strdup, strcat; memset, memcpy */
#include <unistd.h>	/* read, write, size_t */

#include "_getline.h"

/**
 * get_file_index -
 * @file_chain:
 * @count:
 * @desc:
 *
 * Return:
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
	*file_chain = realloc(*file_chain, sizeof(data_buffer) * (*count));
	(*file_chain)[index].desc = desc;
	(*file_chain)[index].length = -1;
	(*file_chain)[index].position = 0;
	(*file_chain)[index].data = malloc(sizeof(char));

	return (index);
}

/**
 * extract_file_data -
 * @file:
 *
 * Return:
 */
void extract_file_data(data_buffer **file)
{
	data_buffer *handle = *file;
	char *file_data, *data_chunk;
	int read_length = 0;

	file_data = malloc(sizeof(char));
	if (!file_data)
		free(file_data);

	handle->length = 0;
	data_chunk = malloc(sizeof(char) * READ_SIZE);
	do { /* incrementally extract all data from given file */
		memset(data_chunk, '\0', READ_SIZE);
		read_length = read(handle->desc, data_chunk, READ_SIZE);
		if (read_length > 0)
		{
			handle->data = realloc(
				handle->data,
				handle->length + read_length + 1);
			if (!handle->data)
			{
				free(handle->data);
				break;
			}
			strncpy(&handle->data[handle->length], data_chunk, read_length);
			handle->length += read_length;
		} else
			break;
	} while (read_length > 0);

	free(data_chunk);
}

/**
 * free_buffers -
 * @count:
 * @buffers:
 *
 * Return:
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
 * _getline -  extract a line from the given file
 * @file_desc: the file id to reference
 *
 * Return: a pointer to the line buffer or NULL upon eof or error
 */
char *_getline(const int desc)
{
	static data_buffer *file_chain;
	static int count;
	data_buffer *file;
	data_buffer line = { .length = 0, .position = 0, .data = NULL };
	char symbol;
	int index = 0;

	if (desc < 0)
		return (free_buffers(&count, &file_chain));

	index = get_file_index(&file_chain, &count, desc);
	if (index < 0)
		return (free_buffers(&count, &file_chain));

	file = &file_chain[index];
	if (file->length < 0)
		extract_file_data(&file);

	line.position = file->position;
	do {
		symbol = file->data[line.position++];
	} while (symbol != '\n' && symbol > 0 && line.position < file->length);

	line.length = line.position - file->position;
	line.data = malloc(sizeof(char) * (line.length + 1));
	if (!line.data)
	{
		free(line.data);
		free(file->data);
		return (NULL);
	}

	memset(line.data, '\0', line.length + 1);
	strncpy(line.data, &file->data[file->position], line.length);

	file->position = line.position;
	if (file->position > file->length) /* terminate */
	{
		free(file->data);
		free(line.data);
		return (NULL);
	}
	if (line.data[line.length - 1] == '\n')
		line.data[line.length - 1] = '\0';
	return (line.data);
}
