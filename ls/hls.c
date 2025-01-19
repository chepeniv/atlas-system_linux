#include "hls.h"

/*
 * sprintf writes to a string
 * can be used to append one string to another if their memory spaces
 * don't overlap
 */

/**
 * sort_args - separates and collects all the arguments passed into flags and
 * paths
 * @argv: all the string arguments passed to the program
 * @argc: the total of arguments passed to the program
 * @opts: where to store the options strings found
 * @num_opts: variable to store the number of options found
 * @dirs: where to store the path strings found
 * @num_dirs: variable to store the number of paths found
 *
 * Return: void
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

/**
 * main - entry point to the program takes an array of strings containing
 * desired directory paths to explore as well as '-' options
 * @argc: the total number of parameters passed to an invocation of this
 * program
 * @argv: an array of pointers to the strings passed to this program
 *
 * Return: 0 or an errno
 */
int main(int argc, char **argv)
{
	DIR **dir_refs;
	char **opt_args = NULL, **dir_args = NULL, **valid_dirs = NULL,
		 **invalid_dirs = NULL;
	int num_opts = 0, num_dirs = 0, num_valid = 0, num_invalid = 0;
	int opt_flags = 0;

	opt_args = malloc(sizeof(void *) * argc);
	dir_args = malloc(sizeof(void *) * argc);

	sort_args(
		argv, argc,
		opt_args, &num_opts,
		dir_args, &num_dirs);

	opt_flags = set_opt_flags(opt_args, num_opts, argv[0]);

	if (opt_flags < 0)
	{
		free(opt_args);
		free(dir_args);
		exit(errno);
	}

	dir_refs = validate_dirs(
		dir_args, &num_dirs,
		&valid_dirs, &num_valid,
		&invalid_dirs, &num_invalid);

	output_invalid(invalid_dirs, num_invalid, argv[0]);
	output_valid(dir_refs, valid_dirs, num_valid);

	for (int d = 0; d < num_valid; d++)
		closedir(dir_refs[d]);

	void *allocs[5] = {dir_refs, dir_args, opt_args, valid_dirs, invalid_dirs};

	free_all(allocs, 5);

	return (errno);
}
