#include <dirent.h>    /* opendir, readdir, closedir */
#include <errno.h>
#include <stdio.h>     /* printf, sprintf, fprintf, perror */
#include <stdlib.h>    /* exit, free, malloc */
#include <sys/types.h>
#include "hls.h"

/* #include <grp.h>       /1* getgrgid *1/ */
/* #include <pwd.h>       /1* getpwuid *1/ */
/* #include <sys/stat.h>  /1* (syscall) lstat *1/ */
/* #include <time.h>      /1* ctime *1/ */
/* #include <unistd.h>    /1* (syscalls) write, readlink *1/ */


/****************
 * struct dirent readdir(DIR *dirp)
 *
 ****************
 * struct dirent *read;
 *
 * while ((read = readdir(dir)))
 *		printf("%s\n", read->d_name);
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
	/* handle the return values of opendir, readdir, and closedir */
	DIR **dir_refs;
	char **opt_args, **dir_args, **valid_dirs, **invalid_dirs;
	const int _1 = 1, _A = 2, _a = 4, _l = 8;
	int opts = 0,
		opt_count = 0,
		dir_count = 0,
		valid_count = 0,
		invalid_count = 0;

	opt_args = malloc(sizeof(void *) * argc);
	dir_args = malloc(sizeof(void *) * argc);

	/* collect options and directory paths */
	for (int i = 1; i < argc; i++)
	{
		if (argv[i][0] == '-')
		{
			opt_args[opt_count] = &argv[i][1]; /* skip the '-' character */
			opt_count++;
		}
		else
		{
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
					exit(errno);
			}
		}
	}

	/* validate directories */
	if (!dir_count)
	{
		dir_refs = malloc(sizeof(DIR *));
		valid_dirs = malloc(sizeof(char *));


		valid_dirs[valid_count++] = ".";
		dir_refs[dir_count++] = opendir(".");
	}
	else
	{
		dir_refs = malloc(sizeof(DIR *) * dir_count);
		valid_dirs = malloc(sizeof(char *) * dir_count);
		invalid_dirs = malloc(sizeof(char *) * dir_count);

		for (int d = 0; d < dir_count; d++)
		{
			DIR *dir = opendir(dir_args[d]);

			if (!dir)
				invalid_dirs[invalid_count++] = dir_args[d];
			else
			{
				valid_dirs[valid_count] = dir_args[d];
				dir_refs[valid_count] = dir;
				valid_count++;
			}
		}
	}

	/* output invalid directory error messages */
	for (int d = 0; d < invalid_count; d++)
		printf("%s: cannot access '%s': No such file or directory \n",
				argv[0],
				invalid_dirs[d]);

	/* output valid directories contents */
	for (int d = 0; d < valid_count; d++)
	{
		struct dirent *dir_item;

		if (valid_count > 1)
			printf("%s:\n", valid_dirs[d]);
		while ((dir_item = readdir(dir_refs[d])))
		{
			char *d_name = dir_item->d_name;

			if (d_name[0] != '.')
				printf("%s  ", d_name);
		}

		printf("\n");
	}

	/* verify options */
	/* if (opts & _A) */
	/*		printf("option 'A' given\n"); */

	/* close opened directories and free allocated memory*/
	for (int d = 0; d < valid_count; d++)
		closedir(dir_refs[d]);

	free(dir_refs);
	free(opt_args);
	free(dir_args);
	free(valid_dirs);
	if (invalid_count)
		free(invalid_dirs);

	/*
	 * fprintf writes to the arbitrary output string given
	 * sprintf writes to a string
	 * can be used to append one string to another if their memory spaces
	 * don't overlap
	 */

	/*
	 * return the last error code (errno ?)
	 */
	return (errno);
}
