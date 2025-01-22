#include "hls.h"

/**
 * get_filter - determines which filter to use based on the opt_flags code
 * @opt_flags: the binary integer to analyze
 *
 * Return: a function of the form 'int (*filter)(char *)' used to filter out
 * strings
 */

int (*get_filter(int opt_flags))(char *)
{
	if (opt_flags & _A)
		return (opt_almost_all_filter);
	else if (opt_flags & _a)
		return (opt_all_filter);
	else
		return (opt_standard_filter);
}

/**
 * get_printer - determines which print method to use based on an opt_flags
 * code given
 * @opt_flags: the binary integer to analyze
 *
 * Return: a function of the form 'void (*printer)(path_data *)' used to
 * format the output of a path given
 */

void (*get_printer(int opt_flags))(path_data *)
{
	if (opt_flags & _l)
		return (opt_long_print);
	else if (opt_flags & _1)
		return (opt_column_print);
	else
		return (opt_standard_print);
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

			switch (c) /* precedence: l > 1 ; A > a */
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
