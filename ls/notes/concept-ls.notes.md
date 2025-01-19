# create your own `ls`

## manipulating directory streams

```c
#include <sys/types.h>
#include <dirent.h>
```

### `opendir()`

(man 3 opendir)

```c
DIR *opendir(const char *name)
```
used to open a directory stream

### `readdir()`

(man 3 readdir)

```c
struct dirent readdir(DIR *dirp)
```
used to browse a directory stream using a `DIR *` returned by `opendir()`

each consecutive call on the same stream returns the next `struct dirent *` in
that directory

example
```c
struct dirent *read;

while ((read = readdir(dir)) != NULL)
	printf("%s\n", read->d_name);
```

### `closedir()`

(man 3 closedir)

```c
int closedir(DIR *dirp)
```
closes the give directory stream

## `lstat()`

(man 2 lstat)

```c
#include <sys/stat.h>

int stat(const char *restrict pathname, struct stat *restrict statbuf);
```
returns information about a file by taking the path to it and a
`struct stat *buffer` wherein the information found will be stored

## types, rights, and time

### types

the `st_mode` field of `struct stat` contains the file type

it can be tested with the following macros
```c
S_ISREG(st_mode) // is it a regular file?
S_ISDIR(st_mode) // is it a directory?
S_ISCHR(st_mode) // is it a character device?
S_ISBLK(st_mode) // is it a block device?
S_ISFIFO(st_mode) // is it a FIFO (named pipe)?
S_ISLNK(st_mode) // is it a symbolic link? (Not in POSIX.1-1996.)
S_ISSOCK(st_mode) // is it a socket? (Not in POSIX.1-1996.)
```
### rights

the rights of a file can also be extracted from the `st_mode` field by
bit-masking
```c
st_mode & S_IRUSR == true // if owner has read permission
st_mode & S_IWUSR == true // if owner has write permission
st_mode & S_IXUSR == true // if owner has execute permission
```

### time

since the `struct timespec st_mtime` field is not easily readable, use the
`char *ctime(strict timspec *time_data)` function (man 3 ctime) to convert it
into a readable string

## groups and users

`struct stat` contains the `st_gid` and `st_uid` ids which can be used with the
`getgrgid()` and `getpwuid()` functions respectively. these functions return
structures described in their man pages getpwuid(3) and getgrgid(3)

