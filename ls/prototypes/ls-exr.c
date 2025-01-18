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

int str_len(char *string)
{
	int len = 0;

	while (string[len] != '\0')
		len++;
	return (len);
}

int main(int argc, char **argv)
{
	char *opts;
	char **opt_args,
		 **valid_dirs,
		 **invalid_dirs;
	int opt_count = 0;
	/* int _A = 0b1000, */
	/* 	_a = 0b0100, */
	/* 	_l = 0b0010, */
	/* 	_1 = 0b0001; */
	/* int valid_opts[4] = { _A, _a, _l, _1}; */

	(void) opts;
	/* (void) valid_opts; */
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
		printf("----\n");
		for (int j = 1; opt_args[i][j] != '\0'; j++)
		{
			char c = opt_args[i][j];
			switch (c)
			{
				case 'A':
					printf("%c is valid\n", c);
					break;
				case 'a':
					printf("%c is valid\n", c);
					break;
				case 'l':
					printf("%c is valid\n", c);
					break;
				case '1':
					printf("%c is valid\n", c);
					break;
				default:
					printf("%c is NOT valid\n", c);
			}
		}
	}

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
