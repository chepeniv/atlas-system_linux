#ifndef _GETLINE_
#define _GETLINE_

/* the number of bytes to extract each iteration */
/* #define READ_SIZE 1024 */
#define READ_SIZE 2048

/**
 * struct _data_buffer - a structure for storing read data along with some
 * metadata
 * @desc: the id assigned to the file by the operating system
 * @length: how long the number of characters are stored within
 * @position: where along the data was the last read point
 * @data: a pointer to a buffer holding the data
 */
typedef struct _data_buffer
{
	int desc;
	int length;
	int position;
	char *data;
} data_buffer;

char *_getline(const int file_desc);
int get_file_index(data_buffer **chain, int *count, int desc);
void extract_file_data(data_buffer **file);
void *free_buffers(int *count, data_buffer **chain);
data_buffer extract_line(data_buffer **file);

#endif /* _GETLINE_ */
