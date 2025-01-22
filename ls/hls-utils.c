#include "hls.h"

path_data *get_path_data(char *path_name)
{
	path_data *entry = malloc(sizeof(path_data));
	struct stat *path_stat = malloc(sizeof(struct stat));
	DIR *path_stream = NULL;
	int errcode = lstat(path_name, path_stat);

	if (!errcode)
	{
		if (S_ISDIR(path_stat->st_mode))
		{
			path_stream = opendir(path_name);
			if (!path_stream)
			{
				errcode = errno;
				free(path_stat);
				path_stat = NULL;
			}
		}
	}
	else
	{
		errcode = errno;
		free(path_stat);
		path_stat = NULL;
	}
	entry->name = path_name;
	entry->stream = path_stream;
	entry->stat = path_stat;
	entry->errcode = errcode;

	return (entry);
}

/**
 * init_path_data_chain - analyze and collect all stat metadata for each path
 * given
 * @path_args: names of all the paths
 * @num_paths: total number of paths given
 *
 * Return: an array of structs containing the extracted info for each path
 */

path_data **init_path_data_chain(char **path_args, int *num_paths)
{
	path_data **path_data_chain;

	if (!(*num_paths))
		path_args[(*num_paths)++] = ".";

	path_data_chain = malloc(sizeof(path_data *) * *num_paths);
	for (int p = 0; p < *num_paths; p++)
	{
		char *path_name = path_args[p];
		path_data_chain[p] = get_path_data(path_name);
	}
	return (path_data_chain);
}

int (*get_filter(int opt_flags))(char *)
{
	if (opt_flags & _A)
		return (opt_almost_all_filter);
	else if (opt_flags & _a)
		return (opt_all_filter);
	else
		return (opt_standard_filter);
}

void (*get_printer(int opt_flags))(path_data *)
{
	if (opt_flags & _l)
		return (opt_long_print);
	else if (opt_flags & _1)
		return (opt_column_print);
	else
		return (opt_standard_print);
}

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

			switch (c) /* precedence: l > 1 ; A > a */
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
 * free_data_chain - frees all nested allocations in the given path_data array
 * as well as the array itself
 * @data_chain: the array to process
 * @num_paths: the length of the array
 */

void free_data_chain(path_data **data_chain, int num_paths)
{
	path_data *path;

	for (int p = 0; p < num_paths; p++)
	{
		path = data_chain[p];
		free(path->stat);
		closedir(path->stream);
		free(path);
	}
	free(data_chain);
}
