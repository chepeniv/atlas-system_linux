#include "hls.h"

/**
 * output_valid - printout the contents of each valid directory path found
 * @dir_refs: an array of pointers to structs used to examine directory
 * contents
 * @valid_dirs: an array of strings containing the names of the valid directory
 * paths
 * @num_valid: total number of valid paths given to the program
 *
 * Return: void
 */
void output_valid(DIR **dir_refs, char **valid_dirs, int num_valid)
{
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
}

/**
 * output_invalid - handles the output messages for all invalid directories
 * passed
 * @invalid_dirs: an array of pointers to the string names of the invalid paths
 * @num_invalid: number of invalid directory paths found
 * @prog_name: the name of the program calling this functions
 *
 * Return: void
 */
void output_invalid(char **invalid_dirs, int num_invalid, char *prog_name)
{
	for (int d = 0; d < num_invalid; d++)
		printf("%s: cannot access '%s': No such file or directory \n",
				prog_name,
				invalid_dirs[d]);
}

/**
 * free_all - frees all elements of an array of pointers to allocated memory
 * @allocs: an array of pointers to allocated memory spaces
 * @length: size of the array
 *
 * Return: void
 */
void free_all(void **allocs, int length)
{
	for (int i = 0; i < length; i++)
		free(allocs[i]);
}


