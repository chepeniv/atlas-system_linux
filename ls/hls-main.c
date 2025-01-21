#include "hls.h"

/**
 * print_paths - traffic control logic for the various print_ calls
 * @program: name the current invocation of this program
 * @data_chain: the path_data array to analyse and extract data from
 * @num_paths: the total number of arguments passed to the current invocation
 */

void print_paths(char *program, path_data **data_chain, int num_paths)
{
	path_data *path;
	struct stat *path_stat;
	int indx_reg[num_paths], num_reg = 0,
		indx_dir[num_paths], num_dir = 0,
		indx_err[num_paths], num_err = 0;

	(void) program;

	for (int p = 0; p < num_paths; p++)
	{
		path = data_chain[p];
		path_stat = path->stat;

		if (!path_stat)
			indx_err[num_err++] = p;
		else if (S_ISREG(path_stat->st_mode))
			indx_reg[num_reg++] = p;
		else if (S_ISDIR(path_stat->st_mode))
			indx_dir[num_dir++] = p;
	}

	if (num_err > 0)
		print_errors(program, data_chain, indx_err, num_err);
	if (num_reg > 0)
	{
		print_reg_paths(data_chain, indx_reg, num_reg);
		if (num_dir > 0)
			printf("\n");
	}
	if (num_dir > 0)
		print_dir_paths(data_chain, indx_dir, num_dir);
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
	/* int opt_flags = 0; */

	opt_args = malloc(sizeof(void *) * argc);
	path_args = malloc(sizeof(void *) * argc);
	sort_args(
		argv, argc,
		opt_args, &num_opts,
		path_args, &num_paths);

	/* if (!(opt_flags = set_opt_flags(opt_args, num_opts, argv[0]))) */
	/* { */
	/* free(opt_args); */
	/* free(path_args); */
	/* exit(errno); */
	/* } */

	path_data_chain = init_path_data_chain(path_args, &num_paths);
	print_paths(argv[0], path_data_chain, num_paths);

	free_data_chain(path_data_chain, num_paths);
	free(opt_args);
	free(path_args);

	return (errno);
}
