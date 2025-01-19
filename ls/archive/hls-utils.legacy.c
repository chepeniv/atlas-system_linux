#include "hls.h"

/**
 * validate_dirs - separates and collects all the directories given into
 * either valid or invalid containers
 * @dir_args: all of the directory paths given to this program
 * @num_dirs: the number of directory paths given
 * @valid_dirs: where to store the valid directory paths strings found
 * @num_valid: where to store the number of total valid directories
 * @invalid_dirs: where to store the invalid directory paths strings found
 * @num_invalid: where to store the number of total invalid directories
 *
 * Return: array of DIR pointers
 */

DIR **validate_dirs(
char **dir_args, int *num_dirs,
char ***valid_dirs, int *num_valid,
char ***invalid_dirs, int *num_invalid)
{
	DIR **dir_refs;
	DIR *dir;

	if (!(*num_dirs))
	{
		dir_refs = malloc(sizeof(DIR *));
		*valid_dirs = malloc(sizeof(char *));
		*invalid_dirs = malloc(sizeof(char *)); /* init for free */


		*valid_dirs[*num_valid] = ".";
		dir_refs[*num_valid] = opendir(".");
		(*num_valid)++;
		(*num_dirs)++;
	}
	else
	{
		dir_refs = malloc(sizeof(DIR *) * *num_dirs);
		*valid_dirs = malloc(sizeof(char *) * *num_dirs);
		*invalid_dirs = malloc(sizeof(char *) * *num_dirs);

		for (int d = 0; d < *num_dirs; d++)
		{
			dir = opendir(dir_args[d]);

			if (!dir)
				(*invalid_dirs)[(*num_invalid)++] = dir_args[d];
			else
			{
				(*valid_dirs)[*num_valid] = dir_args[d];
				dir_refs[*num_valid] = dir;
				(*num_valid)++;
			}
		}
	}
	return (dir_refs);
}
