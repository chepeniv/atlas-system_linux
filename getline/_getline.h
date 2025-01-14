#ifndef _GETLINE_
#define _GETLINE_

/* the number of bytes to extract each iteration */
#define READ_SIZE 2048
#define LINE_SIZE 128

char *_getline(const int file_desc);
void find_line(char *source, char *dest, int pos[1], int length);

#endif /* _GETLINE_ */
