#include <dirent.h>    /* opendir, readdir, closedir */
#include <errno.h>
#include <stdio.h>     /* printf, sprintf, fprintf, perror */
#include <stdlib.h>    /* exit, free, malloc */
#include <sys/types.h>
#include "ls-exr.h"

/* #include <grp.h>       /1* getgrgid *1/ */
/* #include <pwd.h>       /1* getpwuid *1/ */
/* #include <sys/stat.h>  /1* (syscall) lstat *1/ */
/* #include <time.h>      /1* ctime *1/ */
/* #include <unistd.h>    /1* (syscalls) write, readlink *1/ */

/* take the name of a directory and output its contents
 * handle non-existent folders
 * handle the return values of opendir, readdir, and closedir
 */

/****************
 * DIR *opendir(const char *name)
 *
 ****************
 * struct dirent opendir(DIR *dirp)
 *
 * analyses each item of a directory
 * consecutively
 *
 * example:
 *
 * struct dirent *read;
 *
 * while (!(read = readdir(dir))
 * 		printf("%s\n", read->d_name);
 *
 ****************
 * int closedir(DIR *dirp)
 *
 ****************
 * int stat(const char *pathname, struct stat *statbuf)
 *
 * fills statbuf with info about the file given
 */

int main(int argc, char **argv)
{
	char **opt_args, **dir_args, **valid_dirs, **invalid_dirs;
	int opts = 0;
	int opt_count = 0, dir_count = 0;
	const int _1 = 1, _A = 2, _a = 4, _l = 8;

	(void) valid_dirs;
	(void) invalid_dirs;

	opt_args = malloc(sizeof(void *) * argc);
	dir_args = malloc(sizeof(void *) * argc);

	/* collect options and pathnames*/
	for (int i = 1; i < argc; i++)
	{
		if (argv[i][0] == '-')
		{
			opt_args[opt_count] = &argv[i][1]; /* skip '-' character */
			opt_count++;
		} else {
			dir_args[dir_count] = argv[i];
			dir_count++;
		}
	}

	/* validate options */
	for (int i = 0; i < opt_count; i++)
	{
		for (int j = 0; opt_args[i][j] != '\0'; j++)
		{
			char c = opt_args[i][j];
			switch (c)
			{
				case 'A':
					opts |= _A;
					break;
				case 'a':
					opts |= _a;
					break;
				case 'l':
					opts |= _l;
					break;
				case '1':
					opts |= _1;
					break;
				default:
					printf("%s: invalid option -- '%c'\n", argv[0], c);
					free(opt_args);
					free(dir_args);
					/* for 'ls' this is a  "directory not found" error */
					exit(2);
			}
		}
	}

	/* analyze valid options */
	if (opts & _A)
		printf("option 'A' given\n");
	if (opts & _a)
		printf("option 'a' given\n");
	if (opts & _l)
		printf("option 'l' given\n");
	if (opts & _1)
		printf("option '1' given\n");

	/* analyze pathnames arguments */
	printf("\ndirectories given\n");
	for (int d = 0; d < dir_count; d++)
		printf("pathname: %s\n", dir_args[d]);

	free(opt_args);
	free(dir_args);

	/* fprintf writes to the arbitrary output string given */
	/* sprintf writes to a string */
	/* can be used to append one string to another if their memory spaces
	 * don't overlap */

	/*
	 * if no directory given then
	 * 		dirs = current directory
	 * else
	 *		dirs = collect directory names
	 *		move fake directories from dirs into fakedirs
	 *
	 * for fake in fakedirs
	 * 		print error message
	 *
	 * for dir in dirs
	 * 		get content
	 * 		print content
	 *
	 * return the last error code (errno ?)
	 */
	return 0;
}
