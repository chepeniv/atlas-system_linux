#include "hls.h"

/**
 * sort_args - separates and collects all the arguments passed into flags and
 * paths
 * @argv: all the string arguments passed to the program
 * @argc: the total of arguments passed to the program
 * @opts: where to store the options strings found
 * @num_opts: variable to store the number of options found
 * @dirs: where to store the path strings found
 * @num_dirs: variable to store the number of paths found
 */

void sort_args(
char **argv, int argc,
char **opts, int *num_opts,
char **dirs, int *num_dirs)
{
	for (int i = 1; i < argc; i++)
	{
		if (argv[i][0] == '-')
		{
			opts[*num_opts] = &argv[i][1]; /* skip the '-' character */
			(*num_opts)++;
		}
		else
		{
			dirs[*num_dirs] = argv[i];
			(*num_dirs)++;
		}
	}
}

/**
 * output_valid_dirs - printout the contents of each valid directory path found
 * @dir_streams: an array of pointers to structs used to examine directory
 * contents
 * @dir_paths: an array of strings containing the names of the valid directory
 * paths
 * @num_dir: total number of valid paths given to the program
 */

void output_valid_dirs(DIR **dir_streams, char **dir_paths, int num_dir)
{
	for (int d = 0; d < num_dir; d++)
	{
		struct dirent *dir_item;

		if (num_dir > 1)
			printf("%s:\n", dir_paths[d]);
		while ((dir_item = readdir(dir_streams[d])))
		{
			char *d_name = dir_item->d_name;

			if (d_name[0] != '.')
				printf("%s  ", d_name);
		}
		printf("\n");
	}

	for (int d = 0; d < num_dir; d++)
		closedir(dir_streams[d]);
}

/**
 * output_invalid - handles the output messages for all invalid directories
 * passed
 * @invalid_dirs: an array of pointers to the string names of the invalid paths
 * @num_invalid: number of invalid directory paths found
 * @prog_name: the name of the program calling this functions
 */

void output_invalid(char **invalid_dirs, int num_invalid, char *prog_name)
{
	for (int d = 0; d < num_invalid; d++)
		printf("%s: cannot access '%s': No such file or directory \n",
				prog_name,
				invalid_dirs[d]);
}

/**
 * set_opt_flags - takes all the flag parameters given, validates them, and
 * sets the corresponding bit in a flags variable
 * @opt_args: all the options strings found
 * @num_opts: the number of options strings found
 * @prog: the name of the compiled program, used for outputting proper error
 * messages
 *
 * Return: the integer represented bit the resultant bit flags
 */

int set_opt_flags(char **opt_args, int num_opts, char *prog)
{
	int opt_flags = 0;

	for (int i = 0; i < num_opts; i++)
	{
		for (int j = 0; opt_args[i][j] != '\0'; j++)
		{
			char c = opt_args[i][j];

			switch (c)
			{
				case 'A':
					opt_flags |= _A;
					break;
				case 'a':
					opt_flags |= _a;
					break;
				case 'l':
					opt_flags |= _l;
					break;
				case '1':
					opt_flags |= _1;
					break;
				default:
					printf("%s: invalid option -- '%c'\n", prog, c);
					return (-1);
			}
		}
	}
	return (opt_flags);
}

/**
 * free_all - frees all elements of an array of pointers to allocated memory
 * @allocs: an array of pointers to allocated memory spaces
 * @length: size of the array
 */

void free_all(void **allocs, int length)
{
	for (int i = 0; i < length; i++)
		free(allocs[i]);
}


