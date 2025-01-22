#include "hls.h"

path_data *get_path_data(char *path_name)
{
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

	return (entry);
}

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

		path_data_chain[p] = get_path_data(path_name);
	}
	return (path_data_chain);
}

/**
 * free_data_chain - frees all nested allocations in the given path_data array
 * as well as the array itself
 * @data_chain: the array to process
 * @num_paths: the length of the array
 */

void free_data_chain(path_data **data_chain, int num_paths)
{
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
