#include <stdlib.h>	/* malloc, realloc, free */
#include <string.h>	/* strcpy, strncpy, strdup, strcat; memset, memcpy */
#include <unistd.h>	/* read, write, size_t */

#include "_getline.h"

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
	char *chunk = malloc(sizeof(char) * READ_SIZE);
	int read_length = 0;

	file.data = malloc(sizeof(char));
	if (!file.data || !chunk)
	{
		free(chunk);
		free(file.data);
		return (file);
	}

	file.length = 0;
	do { /* incrementally extract all data from given file */
		memset(chunk, '\0', READ_SIZE);
		read_length = read(file_desc, chunk, READ_SIZE);
		if (read_length > 0)
		{
			file.data = realloc(file.data, file.length + read_length + 1);
			if (!file.data)
			{
				free(file.data);
				break;
			}
			strncpy(&file.data[file.length], chunk, read_length);
			file.length += read_length;
		}
		else if (read_length == -1)
			free(file.data);
	} while (read_length > 0);

	free(chunk);
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
	data_buffer line = { .length = 0, .position = 0, .data = NULL };
	char symbol;

	if (file.length < 0)
		file = extract_file_data(file_desc, file);
	if (file.length <= 1) /* abandon empty file */
	{
		free(file.data);
		return (NULL);
	}
	if (file.data[file.position] == '\n') /* move pass newline char */
		file.position++;

	line.position = file.position;
	do {
		symbol = file.data[++line.position];
	} while (symbol != '\n' && symbol != '\r' && symbol > 0 &&
			line.position < (file.length - 1));

	line.length = line.position - file.position;
	line.data = malloc(sizeof(char) * (line.length + 1));
	if (!line.data)
	{
		free(line.data);
		free(file.data);
		return (NULL);
	}

	memset(line.data, '\0', line.length + 1);
	strncpy(line.data, &file.data[file.position], line.length);

	file.position = line.position;
	if (file.position >= file.length) /* terminate */
	{
		free(file.data);
		free(line.data);
		return (NULL);
	}
	return (line.data);
}
