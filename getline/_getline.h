#ifndef _GETLINE_
#define _GETLINE_

/* the number of bytes to extract each iteration */
/* #define READ_SIZE 1024 */
#define READ_SIZE 2048

/**
 * struct _data_buffer - a structure for storing read data along with some metadata
 * @length: how long the number of characters are stored within
 * @position: where along the data was the last read point
 * @data: a pointer to a buffer holding the data
 */
typedef struct _data_buffer
{
	int length;
	int position;
	char *data;
} data_buffer;

char *_getline(const int file_desc);
data_buffer extract_line(data_buffer file);
data_buffer extract_file_data(int file_desc, data_buffer file);

#endif /* _GETLINE_ */
