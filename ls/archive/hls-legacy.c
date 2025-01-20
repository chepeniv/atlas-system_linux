#include "../hls.h"

/**
 * output_valid_dirs - printout the contents of each valid directory path found
 * @dir_streams: an array of pointers to structs used to examine directory
 * contents
 * @dir_paths: an array of strings containing the names of the valid directory
 * paths
 * @num_dir: total number of valid paths given to the program
 * @num_invalid: used to determine how to format output
 */

void output_valid_dirs(
DIR **dir_streams,
char **dir_paths,
int num_dir,
int num_invalid)
{
	for (int d = 0; d < num_dir; d++)
	{
		struct dirent *dir_item;

		if (num_dir > 1 || num_invalid)
			printf("%s:\n", dir_paths[d]);
		while ((dir_item = readdir(dir_streams[d])))
		{
			char *d_name = dir_item->d_name;

			if (d_name[0] != '.')
				printf("%s  ", d_name);
		}
		printf("\n");
		if ((d + 1) != num_dir)
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
	char *error_msg = malloc(sizeof(char) * 128);

	for (int d = 0; d < num_invalid; d++)
	{
		sprintf(error_msg, "%s: cannot access %s",
				prog_name,
				invalid_dirs[d]);
		perror(error_msg);
	}
	free(error_msg);
}

/**
 * output_reg_files - printout to stdout every file found
 * @reg_paths: array containing the file names
 * @num_reg: number of files found
 */

void output_reg_files(char **reg_paths, int num_reg)
{
	if (num_reg)
	{
		for (int r = 0; r < num_reg; r++)
			printf("%s  ", reg_paths[r]);
		printf("\n\n");
	}
}

/**
 * output_valid_paths - printout all valid files and directories
 * @file_stats: array of data structures containing metadata for each valid
 * path found
 * @valid_paths: array of pathnames
 * @num_valid: total number of valid items
 * @num_invalid: used to decide how to format output
 */

void output_valid_paths(
_stat_struct **file_stats,
char **valid_paths,
int num_valid,
int num_invalid)
{
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

	output_reg_files(reg_paths, num_reg);

	dir_streams = malloc(sizeof(DIR *) * num_dir);
	for (int d = 0; d < num_dir; d++)
		dir_streams[d] = opendir(dir_paths[d]);

	output_valid_dirs(dir_streams, dir_paths, num_dir, num_invalid);

	free(reg_paths);
	free(dir_paths);
	free(dir_streams);
}

/**
 * validate_paths - analyze all paths given and determine whether they're valid
 * or not
 * @path_args: an array of all paths passed to the program
 * @num_paths: total number of paths passed
 * @valid_paths: where to store valid path names
 * @num_valid: total number of valid paths found
 * @invalid_paths: where to store invalid path names
 * @num_invalid: total number of invalid paths found
 *
 * Return: a struct stat * array referencing metadata objects for each valid
 * item found
 */

_stat_struct **validate_paths(
char **path_args, int *num_paths,
char ***valid_paths, int *num_valid,
char ***invalid_paths, int *num_invalid)
{
	struct stat **file_stats, *f_stat;
	int validity;

	if (!(*num_paths))
		path_args[(*num_paths)++] = ".";

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

	return (file_stats);
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

int old_main(int argc, char **argv)
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
	output_valid_paths(file_stats, valid_paths, num_valid, num_invalid);

	if (num_valid)
		for (int s = 0; s < num_valid; s++)
			free(file_stats[s]);

	void *allocs[5] = { file_stats, path_args, opt_args, valid_paths,
		invalid_paths};
	free_all(allocs, 5);

	return (errno);
}
