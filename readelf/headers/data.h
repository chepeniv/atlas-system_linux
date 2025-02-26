#ifndef _DATA_
#define _DATA_

char **get_fields(void);
int print_data(char **fields, char **entries);
int process_header_data(unsigned char *raw);

#endif /* _DATA_ */
