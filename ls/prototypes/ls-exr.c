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
	char **opt_args, **valid_dirs, **invalid_dirs;
	int opts = 0;
	int opt_count = 0;
	const int _1 = 1, _A = 2, _a = 4, _l = 8;

	(void) valid_dirs;
	(void) invalid_dirs;

	/* collect options passed */
	opt_args = malloc(sizeof(void *) * argc);
	for (int arg = 1; arg < argc; arg++)
	{
		if (argv[arg][0] == '-') /* && argv[arg][1] != '-' */
		{
			opt_args[opt_count] = argv[arg];
			opt_count++;
		}
	}

	/* validate options passed */
	for (int i = 0; i < opt_count; i++)
	{
		for (int j = 1; opt_args[i][j] != '\0'; j++)
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
					/* for 'ls' this is a  "directory not found" error */
					exit(2);
			}
		}
	}

	if (opts & _A)
		printf("option 'A' given\n");
	if (opts & _a)
		printf("option 'a' given\n");
	if (opts & _l)
		printf("option 'l' given\n");
	if (opts & _1)
		printf("option '1' given\n");

	free(opt_args);

	/* fprintf writes to the arbitrary output string given */
	/* sprintf writes to a string */
	/* can be used to append one string to another if their memory spaces
	 * don't overlap */

	/*
	 * for opt in opts
	 * 		if opt is invalid
	 * 			print error msg along with offending opt
	 * 			return (don't process any further)
	 *
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
