# stpcpy, STRCPY, STRCAT

copy or catenate a string

```c
#include <string.h>

char *stpcpy(char *restrict dst, const char *restrict src);
char *strcpy(char *restrict dst, const char *restrict src);
char *strcat(char *restrict dst, const char *restrict src);
```

## DESCRIPTION

### stpcpy(), strcpy()

These  functions copy the string pointed to by src, into a string at the buffer
pointed to by dst.  The programmer is responsible for allocating a destination
buffer large enough, that is, strlen(src) + 1.  For the difference between the
two functions, see RETURN VALUE.

### strcat()

This function catenates the string pointed to by src, after the string pointed
to by dst (overwriting its terminating null byte).  The programmer is
responsible for  allocating a destination buffer large enough, that is,
strlen(dst) + strlen(src) + 1.


## RETURN VALUE

### stpcpy()

This function returns a pointer to the terminating null byte of the copied
string.

### strcpy(), strcat()

These functions return dst.

----

# STRDUP, strndup, strdupa, strndupa

duplicate a string

```c
#include <string.h>

char *strdup(const char *s);

char *strndup(const char s[.n], size_t n);
char *strdupa(const char *s);
char *strndupa(const char s[.n], size_t n);
```

## DESCRIPTION

The  strdup()  function  returns  a  pointer  to  a  new string which is a
duplicate of the string s.  Memory for the new string is obtained with
malloc(3), and can be freed with free(3).

The strndup() function is similar, but copies at most n bytes.  If s is longer
than n, only n bytes are copied, and a terminating null byte ('\0') is added.

strdupa() and strndupa() are similar, but use alloca(3) to allocate the buffer.

## RETURN VALUE

On success, the strdup() function returns a pointer to the duplicated string.
It returns NULL if insufficient memory was available, with errno set to
indicate the error.

## ERRORS

ENOMEM Insufficient memory available to allocate duplicate string.

----

# MEMSET

fill memory with a constant byte

```c
#include <string.h>

void *memset(void s[.n], int c, size_t n);
```

## DESCRIPTION

The memset() function fills the first n bytes of the memory area pointed to by
s with the constant byte c.

## RETURN VALUE

The memset() function returns a pointer to the memory area s.

----

# stpncpy, STRNCPY

fill a fixed-size buffer with non-null bytes from a string, padding with null
bytes as needed

```c
#include <string.h>

char *strncpy(
	char dst[restrict .dsize],
	const char *restrict src,
	size_t dsize);

char *stpncpy(
	char dst[restrict .dsize],
	const char *restrict src,
	size_t dsize);
```

## DESCRIPTION

These  functions  copy  non-null  bytes from the string pointed to by src into
the array pointed to by dst.  If the source has too few non-null bytes to fill
the destination, the functions pad the destination with trailing null bytes.
If the destination buffer, limited by its size, isn't large enough to hold the
copy, the resulting character sequence  is truncated.  For the difference
between the two functions, see RETURN VALUE.

## RETURN VALUE

### strncpy()

returns dst.

### stpncpy()

returns a pointer to one after the last character in the destination character
sequence.

## CAVEATS

The name of these functions is confusing.  These functions produce a
null-padded character sequence, not a string (see string_copying(7)).
For example:

```c
strncpy(buf, "1", 5);       // { '1',   0,   0,   0,   0 }
strncpy(buf, "1234", 5);    // { '1', '2', '3', '4',   0 }
strncpy(buf, "12345", 5);   // { '1', '2', '3', '4', '5' }
strncpy(buf, "123456", 5);  // { '1', '2', '3', '4', '5' }
```

It's  impossible  to distinguish truncation by the result of the call, from a
character sequence that just fits the destination buffer; truncation should be
detected by comparing the length of the input string with the size of the
destination buffer.

If you're going to use this function in chained calls, it would be useful to
develop a similar function that accepts a pointer to the end (one after the
last element) of the destination buffer instead of its size.

----

# MEMCPY

copy memory area

```c
#include <string.h>

void *memcpy(void dest[restrict .n], const void src[restrict .n], size_t n);
```
## DESCRIPTION

The memcpy() function copies n bytes from memory area src to memory area dest.
The memory areas must not overlap.  Use memmove(3) if the memory areas do
overlap.

## RETURN VALUE

The memcpy() function returns a pointer to dest.
