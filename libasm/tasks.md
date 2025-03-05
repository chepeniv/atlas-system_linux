# task

## 0. strlen (6 pts)

files: `0-strlen.asm`

copycat of `strlen` (3) in x86-64 assembly
prototype: `size_t asm_strlen(const char *text);`

## 1. strcmp (10 pts)

files: `1-strcmp.asm`

copycat of `strcmp` (3) in x86-64 assembly
prototype: `int asm_strcmp(const char *left, const char *right);`

## 2. strncmp (13 pts)

files: `2-strncmp.asm`

copycat of `strncmp` (3) in x86-64 assembly
prototype: `int asm_strncmp(const char *left, const char *right, size_t n);`

## 3. strchr (10 pts)

files: `3-strchr.asm`

copycat of `strchr` (3) in x86-64 assembly
prototype: `int asm_strchr(const char *text, int c);`

## 4. strstr (16 pts)

files: `4-strstr.asm`

copycat of `strstr` (3) in x86-64 assembly
prototype: `char *asm_strstr(const char *text, const char *sequence);`

## 5. memcpy (13 pts)

files: `5-memcpy.asm`

copycat of `memcpy` (3) in x86-64 assembly
prototype: `void *asm_memcpy(void *dest, const void *source, size_t n);`

## 6. putc (8 pts)

files: `6-putc.asm`

write a function that prints a single character to `stdout`
prototype: `size_t asm_putc(int c);`
- wherein `c` is the character's ascii code
- return the total number of bytes written to `stdout`
- use of `syscall` is permitted once in the .asm file

## 7. puts (7 pts)

files: `7-puts.asm` `0-strlen.asm`

write a function that prints a string of characters to `stdout`
prototype: `size_t asm_puts(const char *text);`
- wherein `text` holds the string to be printed
- return the total number of bytes written to `stdout`
- use of _any_ `jump` instruction is _not_ permitted
- calling `0-strlen.asm` is allowed _once_
- use of `syscall` is permitted _once_ in the .asm file

## 8. strcasecmp (15 pts)

files: `8-strcasecmp.asm`

copycat of `strcasecmp` (3) in x86-64 assembly
prototype: `int asm_strcasecmp(const char *left, const char *right);`

## 9. strncasecmp (18 pts)

files: `9-strncasecmp.asm`

copycat of `strncasecmp` (3) in x86-64 assembly
prototype: `int asm_strncasecmp(const char *left, const char *right, size_t n);`

## 10. strspn (10 pts)

files: `10-strspn.asm`

copycat of `strspn` (3) in x86-64 assembly
prototype: `size_t asm_strspn(const char *text, const char *accept);`

## 11. strcspn (11 pts)

files: `11-strcspn.asm`

copycat of `strcspn` (3) in x86-64 assembly
prototype: `size_t asm_strcspn(const char *text, const char *reject);`

## 12. strpbrk (10 pts)

files: `12-strpbrk.asm`

copycat of `strpbrk` (3) in x86-64 assembly
prototype: `char *asm_strpbrk(const char *text, const char *accept);`
