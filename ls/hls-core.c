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
		path_data_chain[p] = entry;
	}
	return (path_data_chain);
}

/**
 * print_errors - analyses the path_data array given for errors outputs the
 * appropriate error message
 * @program: name of the invocation of this program
 * @data_chain: pointer to the path_data array
 * @indices: int array holding the positions in data_chain which contain errors
 * @num_err: total number of error indices
 */

void print_errors(
char *program,
path_data **data_chain,
int *indices,
int num_err)
{
	path_data *path;
	char *path_name, *err_msg, *msg_buf = malloc(sizeof(char) * 128);
	int path_err;

	/* output invalid paths */
	for (int e = 0; e < num_err; e++)
	{
		path = data_chain[indices[e]];
		path_name = path->name;
		path_err = path->errcode;
		errno = path_err;

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

	free(msg_buf);
}

/**
 * print_reg_paths - extracts and prints the names of all valid regular files
 * in the path_data array given
 * @data_chain: pointer to the path_data array
 * @indices: an integer array holding the positions of data_chain which are
 * regular paths
 * @num_reg: total number of regular file indices
 */

void print_reg_paths(path_data **data_chain, int *indices, int num_reg)
{
	path_data *path;

	for (int r = 0; r < num_reg; r++)
	{
		path = data_chain[indices[r]];

		printf("%s  ", path->name); /*USE FUNCTION POINTER */
	}
	printf("\n");
}

/**
 * print_dir_contents - given a directory stream, print out all of its contents
 * @dir_stream: directory stream to probe
 */

void print_dir_contents(DIR *dir_stream)
{
	struct dirent *dir_item;

	while ((dir_item = readdir(dir_stream)))
	{
		char *dir_name = dir_item->d_name;

		if (dir_name[0] != '.')
			printf("%s  ", dir_name); /*USE FUNCTION POINTER */
	}

	printf("\n");
}

/**
 * print_dir_paths - extracts and prints the contents of all valid directories
 * in the path_data array given
 * @data_chain: pointer to the path_data array
 * @indices: length of the path_data array
 * @num_dir: length of the path_data array
 */

void print_dir_paths(path_data **data_chain, int *indices, int num_dir)
{
	path_data *path;
	DIR *path_stream;

	for (int d = 0; d < num_dir; d++)
	{
		path = data_chain[indices[d]];
		path_stream = path->stream;

		if (path->errcode)
			continue;
		else if ((num_dir == 1) && S_ISDIR(path->stat->st_mode))
			print_dir_contents(path_stream);
		else if (S_ISDIR(path->stat->st_mode))
		{
			printf("%s:\n", path->name);
			print_dir_contents(path_stream);
			if ((d + 1) != num_dir)
				printf("\n");
		}
	}
}
