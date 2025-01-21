#include "hls.h"

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
	/* int opt_flags = 0; */

	opt_args = malloc(sizeof(void *) * argc);
	path_args = malloc(sizeof(void *) * argc);
	sort_args(
		argv, argc,
		opt_args, &num_opts,
		path_args, &num_paths);

	/* if (!(opt_flags = set_opt_flags(opt_args, num_opts, argv[0]))) */
	/* { */
	/* 	free(opt_args); */
	/* 	free(path_args); */
	/* 	exit(errno); */
	/* } */

	path_data_chain = init_path_data_chain(path_args, &num_paths);
	print_paths(argv[0], path_data_chain, num_paths);

	free_data_chain(path_data_chain, num_paths);
	free(opt_args);
	free(path_args);

	return (errno);
}
