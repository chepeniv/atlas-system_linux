#ifndef _GETLINE_
#define _GETLINE_

/* the number of bytes to extract each iteration */
/* #define READ_SIZE 1024 */
#define READ_SIZE 2048

typedef struct _data_buffer {
	int length;
	int position;
	char *data;
} data_buffer;

char *_getline(const int file_desc);
/* void find_line(char *source, char *dest, int pos[1], int length); */

#endif /* _GETLINE_ */
