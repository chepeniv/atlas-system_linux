#include "hls.h"

/* validate all none . files */
int opt_standard_filter(char *path_name)
{
	if (path_name[0] != '.')
		return (1);

	return (0);
}

void opt_standard_print(path_data *path)
{
	printf("%s  ", path->name);
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
	path_data **path_data_chain;
	char **opt_args = NULL, **path_args = NULL;
	int num_opts = 0, num_paths = 0;
	int opt_flags = 0;
	int (*filter)(char *);
	void (*printer)(path_data *);

	opt_args = malloc(sizeof(void *) * argc);
	path_args = malloc(sizeof(void *) * argc);
	sort_args(
		argv, argc,
		opt_args, &num_opts,
		path_args, &num_paths);

	opt_flags = set_opt_flags(opt_args, num_opts, argv[0]);
	if (opt_flags < 0)
	{
		free(opt_args);
		free(path_args);
		exit(errno);
	}

	filter = get_filter(opt_flags);
	printer = get_printer(opt_flags);
	path_data_chain = init_path_data_chain(path_args, &num_paths);
	print_paths(filter, printer, argv[0], path_data_chain, num_paths);

	free_data_chain(path_data_chain, num_paths);
	free(opt_args);
	free(path_args);

	return (errno);
}
