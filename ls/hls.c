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

void output_valid_paths(
struct stat **file_stats,
char **valid_paths,
int num_valid)
{
	/* struct stat *handler = *file_stats; */
	char **reg_paths, **dir_paths;
	int num_reg = 0, num_dir = 0;
	DIR **dir_streams;

	reg_paths = malloc(sizeof(char *) * num_valid);
	dir_paths = malloc(sizeof(char *) * num_valid);

	for (int p = 0; p < num_valid; p++)
	{
		mode_t mode = file_stats[p]->st_mode;

		if (S_ISDIR(mode))
			dir_paths[num_dir++] = valid_paths[p];
		else
			reg_paths[num_reg++] = valid_paths[p];
	}

	for (int r = 0; r < num_reg; r++)
		printf("%s  ", reg_paths[r]);
	printf("\n");

	dir_streams = malloc(sizeof(DIR *) * num_dir);
	for (int d = 0; d < num_dir; d++)
		dir_streams[d] = opendir(dir_paths[d]);

	output_valid_dirs(dir_streams, dir_paths, num_dir);

	free(reg_paths);
	free(dir_paths);
	free(dir_streams);
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

struct stat **validate_paths(
char **path_args, int *num_paths,
char ***valid_paths, int *num_valid,
char ***invalid_paths, int *num_invalid)
{
	struct stat **file_stats, *f_stat;
	int validity;

	if (!(*num_paths))
	{
		file_stats = malloc(sizeof(struct stat *));
		f_stat = malloc(sizeof(struct stat));
		*valid_paths = malloc(sizeof(char *));
		*invalid_paths = malloc(sizeof(char *)); /* init for free */

		*valid_paths[*num_valid] = ".";
		validity = lstat(".", f_stat);
		if (!validity)
		{
			file_stats[(*num_valid)++] = f_stat;
			(*num_paths)++;
		}
	} else
	{
		file_stats = malloc(sizeof(struct stat *) * *num_paths);
		*valid_paths = malloc(sizeof(char *) * *num_paths);
		*invalid_paths = malloc(sizeof(char *) * *num_paths);

		for (int p = 0; p < *num_paths; p++)
		{
			f_stat = malloc(sizeof(struct stat));
			validity = lstat(path_args[p], f_stat);
			if (!validity)
			{
				(*valid_paths)[*num_valid] = path_args[p];
				file_stats[*num_valid] = f_stat;
				(*num_valid)++;
			}
			else
			{
				(*invalid_paths)[(*num_invalid)++] = path_args[p];
				free(f_stat);
			}
		}
	}
	return (file_stats);
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

	opt_flags = set_opt_flags(opt_args, num_opts, argv[0]);

	if (opt_flags < 0)
	{
		free(opt_args);
		free(path_args);
		exit(errno);
	}

	file_stats = validate_paths(
		path_args, &num_paths,
		&valid_paths, &num_valid,
		&invalid_paths, &num_invalid);

	output_invalid(invalid_paths, num_invalid, argv[0]);
	output_valid_paths(file_stats, valid_paths, num_valid);

	for (int s = 0; s < num_paths; s++)
		free(file_stats[s]);
	void *allocs[5] = { file_stats, path_args, opt_args, valid_paths,
		invalid_paths};
	free_all(allocs, 5);

	return (errno);
}
