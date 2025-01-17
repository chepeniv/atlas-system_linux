# c - ls

it is recommended that the entirety of the project be looked at before
commencing

## resources

- [intranet concept: ls](https://intranet.hbtn.io/concepts/71)
- `man ls`

## objectives

- how does `ls` work
- what are all the functions used by `ls`

## requirements

- all `c` programs will be compiled using the flags
  `-Wall -Werror -Wextra -pedantic`
- `README.md` are mandatory at the root of each *project* directory
- code should conform to the `Betty` style
	- it is checked with [betty-style.pl]() and [betty-doc.pl]()
- all headers should be include guarded
- no more than 6 functions are permitted in `_getline.c`
- `valgrind` must pass with no leaks

### allowed functions and system calls

#### functions (man 3)

----
```c
#include <dirent.h>
#include <sys/types.h>
```
- `DIR *opendir(const char *name)`
- `struct dirent *readdir(DIR *dirp)`
- `int closedir(DIR *dirp)`

----
```c
#include <stdlib.h>
```
- `void exit(int status)`
- `free()`
- `malloc()`

----
```c
#include <stdio.h>
#include <errno.h> /* defines errno (set by sys calls) used by perror */
```
- `void perror(const char *s)`
- `printf()`
- `sprintf()`
- `fprintf()`

----
```c
#include <time.h>
```
- `char *ctime(const time_t *timep)`

----
```c
#include <pwd.h>
#include <sys/types.h>
```
- `struct passwd *getpwuid(uid_t uid)`

----
```c
#include <grp.h>
#include <sys/types.h>
```
- `struct group *getgrgid(gid_t gid)`

#### system calls (man 2)

```c
#include <unistd.h>
```
- `write()`
- `ssize_t readlink(
	const char *restrict pathname,
	char *restrict buf,
	size_t bufsize)`

----
```c
#include <sys/stat.h>
```
- `int lstat(
	const char *restrict pathname,
	structstat *restrict statbuf)`

### compilation

`gcc -Wall -Werror -Wextra -pedantic *. -o hls`

### testing

the output of `hls` should match the output of `/usr/bin/ls`

### details

unless explicitly stated otherwise, don't really worry about spacing or sorting
