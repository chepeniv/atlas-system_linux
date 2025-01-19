#include "hls.h"
#include <sys/stat.h>

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

struct stat **validate_paths(
char **path_args, int *num_paths,
char ***valid_paths, int *num_valid,
char ***invalid_paths, int *num_invalid)
{
	struct stat **file_stats, *f_stat;
	int validity;
	char *pwd = ".";

	/* if no paths given select current directory */
	if (!(*num_paths))
	{
		file_stats = malloc(sizeof(struct stat *));
		f_stat = malloc(sizeof(struct stat));

		*valid_paths = malloc(sizeof(char *));
		*invalid_paths = malloc(sizeof(char *)); /* init for free */

		*valid_paths[*num_valid] = pwd;
		validity = lstat(pwd, f_stat);
		if (!validity)
		{
			file_stats[*num_valid] = f_stat;
			(*num_valid)++;
			(*num_paths)++;
		}
	}
	else
	{
		file_stats = malloc(sizeof(struct stat *) * *num_paths);
		*valid_paths = malloc(sizeof(char *) * *num_paths);
		*invalid_paths = malloc(sizeof(char *) * *num_paths);

		/* separate valid from invalid paths */
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

	for(int s = 0; s < num_paths; s++)
		free(file_stats[s]);
	void *allocs[5] = { file_stats, path_args, opt_args, valid_paths,
		invalid_paths};
	free_all(allocs, 5);

	return (errno);
}
