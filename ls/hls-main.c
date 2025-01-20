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
	path_data *path_data_chain;

	struct stat **file_stats;

	char **opt_args = NULL, **path_args = NULL, **valid_paths = NULL,
		 **invalid_paths = NULL;

	int num_opts = 0, num_paths = 0, num_valid = 0, num_invalid = 0;

	int opt_flags = 0;

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

	output_invalid(invalid_paths, num_invalid, argv[0]);
	output_valid_paths(file_stats, valid_paths, num_valid, num_invalid);

	if (num_valid)
		for (int s = 0; s < num_valid; s++)
			free(file_stats[s]);

	void *allocs[5] = { file_stats, path_args, opt_args, valid_paths,
		invalid_paths};
	free_all(allocs, 5);

	return (errno);
}
