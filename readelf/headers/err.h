#ifndef _ERR_
#define _ERR_

#include <err.h>
#include <errno.h>
#include <error.h>

#define W_NOARG 200
#define E_NELF  201
#define E_NFILE ENOENT
#define E_NREAD EROFS

int err_print(char *procname, char *item);

#endif /* _ERR_ */
