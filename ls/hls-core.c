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

/**
 * print_errors - analyses the path_data array given for errors outputs the
 * appropriate error message
 * @program: name of the invocation of this program
 * @data_chain: pointer to the path_data array
 * @num_paths: length of the path_data array
 */

void print_errors(char *program, path_data **data_chain, int num_paths)
{
	path_data *path;
	char *path_name, *err_msg, *msg_buf = malloc(sizeof(char) * 128);
	int path_err;

	/* output invalid paths */
	for (int p = 0; p < num_paths; p++)
	{
		path = data_chain[p];
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
 * @num_paths: length of the path_data array
 */

void print_reg_paths(path_data **data_chain, int num_paths)
{
	path_data *path;
	char *path_name;
	mode_t path_mode;

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
}

/**
 * print_dir_paths - extracts and prints the contents of all valid directories
 * in the path_data array given
 * @data_chain: pointer to the path_data array
 * @num_paths: length of the path_data array
 */

void print_dir_paths(path_data **data_chain, int num_paths)
{
	path_data *path;
	DIR *path_stream;
	struct dirent *dir_item;

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
}
