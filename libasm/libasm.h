#ifndef _LIBASM_
#define _LIBASM_

#include <sys/types.h>

size_t asm_strlen(const char *text);
int    asm_strcmp(const char *left, const char *right);
int    asm_strncmp(const char *left, const char *right, size_t n);
int    asm_strchr(const char *text, int c);
char  *asm_strstr(const char *text, const char *sequence);
void  *asm_memcpy(void *dest, const void *source, size_t n);
size_t asm_putc(int c);
size_t asm_puts(const char *text);
int    asm_strcasecmp(const char *left, const char *right);
int    asm_strncasecmp(const char *left, const char *right, size_t n);
size_t asm_strspn(const char *text, const char *accept);
size_t asm_strcspn(const char *text, const char *reject);
char  *asm_strpbrk(const char *text, const char *accept);

#endif /* _LIBASM_ */
