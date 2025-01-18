#include "hls.h"

const int _1 = 1, _A = 2, _a = 4, _l = 8;

/****************
 * struct dirent readdir(DIR *dirp)
 *
 ****************
 * struct dirent *read;
 *
 * while ((read = readdir(dir)))
 *		printf("%s\n", read->d_name);
 *
 ****************
 * int closedir(DIR *dirp)
 *
 ****************
 * int stat(const char *pathname, struct stat *statbuf)
 *
 * fills statbuf with info about the file given
 */

/*
 * fprintf writes to the arbitrary output string given
 * sprintf writes to a string
 * can be used to append one string to another if their memory spaces
 * don't overlap
 */

void sort_opts_dirs(
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

int main(int argc, char **argv)
{
	DIR **dir_refs;
	char **opt_args, **dir_args, **valid_dirs, **invalid_dirs;
	int num_opts = 0, num_dirs = 0, num_valid = 0, num_invalid = 0;
	int opt_flags = 0;

	opt_args = malloc(sizeof(void *) * argc);
	dir_args = malloc(sizeof(void *) * argc);

	sort_opts_dirs(
		argv, argc,
		opt_args, &num_opts,
		dir_args, &num_dirs);

	opt_flags = set_opt_flags(opt_args, num_opts, argv[0]);

	if (opt_flags < 0)
	{
		free(opt_args);
		free(dir_args);
		exit(errno);
	}

	/* validate directories */
	if (!num_dirs)
	{
		dir_refs = malloc(sizeof(DIR *));
		valid_dirs = malloc(sizeof(char *));
		invalid_dirs = malloc(sizeof(char *)); /* init for free */


		valid_dirs[num_valid++] = ".";
		dir_refs[num_dirs++] = opendir(".");
	}
	else
	{
		dir_refs = malloc(sizeof(DIR *) * num_dirs);
		valid_dirs = malloc(sizeof(char *) * num_dirs);
		invalid_dirs = malloc(sizeof(char *) * num_dirs);

		for (int d = 0; d < num_dirs; d++)
		{
			DIR *dir = opendir(dir_args[d]);

			if (!dir)
				invalid_dirs[num_invalid++] = dir_args[d];
			else
			{
				valid_dirs[num_valid] = dir_args[d];
				dir_refs[num_valid] = dir;
				num_valid++;
			}
		}
	}

	/* output invalid directory error messages */
	for (int d = 0; d < num_invalid; d++)
		printf("%s: cannot access '%s': No such file or directory \n",
				argv[0],
				invalid_dirs[d]);

	/* output valid directories contents */
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

	/* verify options */
	/* if (opt_flags & _A) */
	/*		printf("option 'A' given\n"); */

	/* close opened directories and free allocated memory*/
	for (int d = 0; d < num_valid; d++)
		closedir(dir_refs[d]);

	free(dir_refs);
	free(opt_args);
	free(dir_args);
	free(valid_dirs);
	free(invalid_dirs);

	return (errno);
}
