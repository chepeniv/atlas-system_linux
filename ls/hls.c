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

void print_paths(char *program, path_data **data_chain, int num_paths)
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
				errno = ENOENT;
				err_msg = "cannot access";
				break;
			case EACCES:
				errno = EACCES;
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
