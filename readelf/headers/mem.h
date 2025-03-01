#ifndef _MEM_
#define _MEM_

int mem_alloc(void **buff, int size, int len);
int nullify(void **series, int len);
char *setup_str_mem(char *text, int len);
void free_text_array(char **text);

#endif /* _MEM_ */
