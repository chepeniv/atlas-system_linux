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
}
