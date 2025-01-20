# struct stat

<!--
                   _
  /\ /\/V\____/V\/V \
 /  / //( Oo oO)\X \ \
 \  | \\_,  '',_// /  |
  \ |  \        / /   /

-->

```c
#include <sys/stat.h>

struct stat {
   dev_t      st_dev;      /* ID of device containing file */
   ino_t      st_ino;      /* Inode number */
   mode_t     st_mode;     /* File type and mode */
   nlink_t    st_nlink;    /* Number of hard links */
   uid_t      st_uid;      /* User ID of owner */
   gid_t      st_gid;      /* Group ID of owner */
   dev_t      st_rdev;     /* Device ID (if special file) */
   off_t      st_size;     /* Total size, in bytes */
   blksize_t  st_blksize;  /* Block size for filesystem I/O */
   blkcnt_t   st_blocks;   /* Number of 512 B blocks allocated */

   struct timespec  st_atim;  /* Time of last access */
   struct timespec  st_mtim;  /* Time of last modification */
   struct timespec  st_ctim;  /* Time of last status change */

#define st_atime  st_atim.tv_sec  /* Backward compatibility */
#define st_mtime  st_mtim.tv_sec
#define st_ctime  st_ctim.tv_sec
};
```

## description

Describes information about a file.

### fields

`st_dev`

- describes  the device on which this file resides. (The major(3) and minor(3)
  macros may be useful to decompose the device ID in this field.)

`st_ino`

- the file's inode number.

`st_mode`

- the file type and mode. See inode(7) for further information.

`st_nlink`

- the number of hard links to the file.

`st_uid`

- the user ID of the owner of the file.

`st_gid`

- the ID of the group owner of the file.

`st_rdev`

- describes the device that this file (inode) represents.

`st_size`

- gives the size of the file (if it is a regular file or a symbolic link) in
  bytes.  The size of a symbolic link is the length of the pathname it
  contains, without a terminating null byte.

`st_blksize`

- gives the "preferred" block size for efficient filesystem I/O.

`st_blocks`

- indicates the number of blocks allocated to the file, in  512-byte units.
  (This may be smaller than st_size/512 when the file has holes.)

`st_atime`

- the time of the last access of file data.

`st_mtime`

- the time of last modification of file data.

`st_ctime`

- the file's last status change timestamp (time of last change to the inode).

For further information on the above fields, see inode(7).

## history

Old kernels and old standards did not support nanosecond timestamp fields.
Instead, there were three timestamp fields—st_atime, st_mtime, and
st_ctime—typed  as  time_t that recorded timestamps with one-second precision.

Since  Linux 2.5.48, the stat structure supports nanosecond resolution for the
three file timestamp fields.  The nanosecond components of each  timestamp  are
available via  names  of  the  form  st_atim.tv_nsec,  if  suitable  test
macros are defined. Nanosecond timestamps were standardized in POSIX.1-2008,
and,  starting  with  glibc 2.12,  glibc  exposes  the  nanosecond component
names if `_POSIX_C_SOURCE` is defined with the value 200809L or greater, or
`_XOPEN_SOURCE` is defined with the value 700 or greater.  Up to and including
glibc 2.19, the definitions of the nanoseconds  components  are  also  defined
if `_BSD_SOURCE` or `_SVID_SOURCE` is defined.  If none of the aforementioned
macros are defined, then the nanosecond values are exposed with names of the
form st_atimensec.
