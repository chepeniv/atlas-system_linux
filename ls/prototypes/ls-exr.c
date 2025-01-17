#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

#include "ls-exr.h"

/* take the name of a directory and output its contents
 * handle non-existent folders
 * handle the return values of opendir, readdir, and closedir
 */

int main(int argc, char **argv)
{
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

	/*
	 * VARIABLES:
	 *
	 * char **passed_opts, **realdirs, **fakedirs
	 * char *opts
	 *
	 * PSEUDO CODE:
	 *
	 * collect passed_opts
	 *
	 * for opt in passed_opts
	 * 		if opt is invalid
	 * 			print error msg along with offending opt
	 * 			return (don't process any further opts)
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
	 *
	 */
}
