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

/*
 * fprintf writes to the arbitrary output string given
 * sprintf writes to a string
 * can be used to append one string to another if their memory spaces
 * don't overlap
 */

int main(int argc, char **argv)
{
	DIR **dir_refs;
	char **opt_args, **dir_args, **valid_dirs, **invalid_dirs;
	int opts = 0, num_opts = 0, num_dirs = 0, num_valid = 0, num_invalid = 0;
	const int _1 = 1, _A = 2, _a = 4, _l = 8;

	opt_args = malloc(sizeof(void *) * argc);
	dir_args = malloc(sizeof(void *) * argc);

	/* collect options and directory paths */
	for (int i = 1; i < argc; i++)
	{
		if (argv[i][0] == '-')
		{
			opt_args[num_opts] = &argv[i][1]; /* skip the '-' character */
			num_opts++;
		}
		else
		{
			dir_args[num_dirs] = argv[i];
			num_dirs++;
		}
	}

	/* validate options */
	for (int i = 0; i < num_opts; i++)
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
	if (!num_dirs)
	{
		dir_refs = malloc(sizeof(DIR *));
		valid_dirs = malloc(sizeof(char *));


		valid_dirs[num_valid++] = ".";
		dir_refs[num_dirs++] = opendir(".");
	}
	else
	{
		dir_refs = malloc(sizeof(DIR *) * num_dirs);
		valid_dirs = malloc(sizeof(char *) * num_dirs);
		invalid_dirs = malloc(sizeof(char *) * num_dirs);

		for (int d = 0; d < num_dirs; d++)
		{
			DIR *dir = opendir(dir_args[d]);

			if (!dir)
				invalid_dirs[num_invalid++] = dir_args[d];
			else
			{
				valid_dirs[num_valid] = dir_args[d];
				dir_refs[num_valid] = dir;
				num_valid++;
			}
		}
	}

	/* output invalid directory error messages */
	for (int d = 0; d < num_invalid; d++)
		printf("%s: cannot access '%s': No such file or directory \n",
				argv[0],
				invalid_dirs[d]);

	/* output valid directories contents */
	for (int d = 0; d < num_valid; d++)
	{
		struct dirent *dir_item;

		if (num_valid > 1)
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
	for (int d = 0; d < num_valid; d++)
		closedir(dir_refs[d]);

	free(dir_refs);
	free(opt_args);
	free(dir_args);
	free(valid_dirs);
	if (num_invalid)
		free(invalid_dirs);

	return (errno);
}
