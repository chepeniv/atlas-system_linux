#include "hls.h"

/******** OPTIONS ********/

/******** FILTERS ********/

/**
 * opt_standard_filter - the default filter function
 * @path_name: the path name to analyze
 *
 * Return: 0 to reject the path, 1 to accept it
 */

int opt_standard_filter(char *path_name)
{
	if (path_name[0] != '.')
		return (1);

	return (0);
}

/**
 * opt_all_filter - doesn't filter out any path
 * @path_name: (ignored)
 *
 * Return: always returns 1 to accept
 */

int opt_all_filter(char *path_name)
{
	(void) path_name;
	return (1);
}

/**
 * opt_almost_all_filter - filters out only the implied . and .. directories
 * @name: the name of the path to analyze
 *
 * Return: 0 to reject, 1 to accept
 */

int opt_almost_all_filter(char *name)
{
	if ((name[0] == '.' && name[1] == '\0') ||
		(name[0] == '.' && name[1] == '.' && name[2] == '\0'))
		return (0);

	return (1);
}

/******** PRINTERS ********/

/**
 * opt_column_print - option for outputting all items into a single column
 * @path: the struct to process for output
 */

void opt_column_print(path_data *path)
{
	printf("%s\n", path->name);
}

/**
 * opt_standard_print - the default output formatting
 * @path: the path to printout information from
 */

void opt_standard_print(path_data *path)
{
	printf("%s  ", path->name);
}
