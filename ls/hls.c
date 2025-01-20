#include "hls.h"

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
					errcode = errno;
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

		path_data_chain[p] = entry;
	}

	return (path_data_chain);
}

void print_path_data(char *program, path_data **data_chain, int num_paths)
{
	char *path_name, *err_msg, *msg_buf = malloc(sizeof(char) * 128);
	path_data *path;
	struct dirent *dir_item;
	DIR *path_stream;
	int path_err;
	/* int indx_reg[num_paths], indx_dir[num_paths], indx_err[num_paths]; */
	mode_t path_mode;

	/* output invalid paths */
	for (int p = 0; p < num_paths; p++)
	{
		path = data_chain[p];
		path_name = path->name;
		path_err = path->errcode;

		if (!path_err)
			continue;

		switch (path_err)
		{
			case ENOENT:
				err_msg = "cannot access";
				break;
			case EACCES:
				err_msg = "cannot open directory";
				break;
		}

		sprintf(msg_buf, "%s: %s %s", program, err_msg, path_name);
		perror(msg_buf);
	}

	/* output valid reg files*/
	for (int p = 0; p < num_paths; p++)
	{
		path = data_chain[p];

		if (path->stat)
		{
			path_name = path->name;
			path_mode = path->stat->st_mode;

			if (S_ISREG(path_mode))
				printf("%s  ", path_name);
		}
	}
	printf("\n\n");

	/* output each valid directory's contents*/
	for (int p = 0; p < num_paths; p++)
	{
		path = data_chain[p];
		path_stream = path->stream;

		if (!path->errcode && path->stat && S_ISDIR(path->stat->st_mode))
		{
			printf("%s:\n", path->name);
			while ((dir_item = readdir(path_stream)))
			{
				char *dir_name = dir_item->d_name;

				if (dir_name[0] != '.')
					printf("%s  ", dir_name);
			}
			printf("\n\n");
		}
	}

	free(msg_buf);
}

void free_data_chain(path_data **data_chain, int num_paths){
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

/*/1** */
/* * main - entry point to the program takes an array of strings containing */
/* * desired directory paths to explore as well as '-' options */
/* * @argc: the total number of parameters passed to an invocation of this */
/* * program */
/* * @argv: an array of pointers to the strings passed to this program */
/* * */
/* * Return: 0 or an errno */
/* *1/ */

/*int main(int argc, char **argv) */
/*{ */
/*	struct stat **file_stats; */
/*	char **opt_args = NULL, **path_args = NULL, **valid_paths = NULL, */
/*		 **invalid_paths = NULL; */
/*	int num_opts = 0, num_paths = 0, num_valid = 0, num_invalid = 0; */
/*	int opt_flags = 0; */

/*	opt_args = malloc(sizeof(void *) * argc); */
/*	path_args = malloc(sizeof(void *) * argc); */

/*	sort_args( */
/*		argv, argc, */
/*		opt_args, &num_opts, */
/*		path_args, &num_paths); */

/*	opt_flags = set_opt_flags(opt_args, num_opts, argv[0]); */

/*	if (opt_flags < 0) */
/*	{ */
/*		free(opt_args); */
/*		free(path_args); */
/*		exit(errno); */
/*	} */

/*	file_stats = validate_paths( */
/*		path_args, &num_paths, */
/*		&valid_paths, &num_valid, */
/*		&invalid_paths, &num_invalid); */

/*	output_invalid(invalid_paths, num_invalid, argv[0]); */
/*	output_valid_paths(file_stats, valid_paths, num_valid, num_invalid); */

/*	if (num_valid) */
/*		for (int s = 0; s < num_valid; s++) */
/*			free(file_stats[s]); */

/*	void *allocs[5] = { file_stats, path_args, opt_args, valid_paths, */
/*		invalid_paths}; */
/*	free_all(allocs, 5); */

/*	return (errno); */
/*} */
