#include "hls.h"

void output_valid(DIR **dir_refs, char **valid_dirs, int num_valid)
{
	for (int d = 0; d < num_valid; d++)
	{
		struct dirent *dir_item;

		if (num_valid > 1)
			printf("%s:\n", valid_dirs[d]);
		while ((dir_item = readdir(dir_refs[d])))
		{
			char *d_name = dir_item->d_name;

			if (d_name[0] != '.')
				printf("%s  ", d_name);
		}

		printf("\n");
	}
}

void output_invalid(char **invalid_dirs, int num_invalid, char *prog_name)
{
	for (int d = 0; d < num_invalid; d++)
		printf("%s: cannot access '%s': No such file or directory \n",
				prog_name,
				invalid_dirs[d]);
}

void free_all(void **allocations, int count)
{
	for (int i = 0; i < count; i++)
		free(allocations[i]);
}


