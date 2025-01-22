#include "hls.h"

/**
 * print_paths - traffic control logic for the various print_ calls
 * @program: name the current invocation of this program
 * @data_chain: the path_data array to analyse and extract data from
 * @num_paths: the total number of arguments passed to the current invocation
 */

void print_paths(char *program, path_data **data_chain, int num_paths)
{
	/* WORK: TAKE AN opt_print() AND AN opt_filter() FUNCTION */

	path_data *path;
	struct stat *path_stat;
	int indx_reg[num_paths], num_reg = 0,
		indx_dir[num_paths], num_dir = 0,
		indx_err[num_paths], num_err = 0;

	/* sort-out the regular, directory, and error paths */
	for (int p = 0; p < num_paths; p++)
	{
		path = data_chain[p];
		path_stat = path->stat;

		if (!path_stat)
			indx_err[num_err++] = p;
		else if (S_ISREG(path_stat->st_mode))
			indx_reg[num_reg++] = p;
		else if (S_ISDIR(path_stat->st_mode))
			indx_dir[num_dir++] = p;
	}

	/* traffic control the call of the print functions */
	if (num_err > 0)
		print_errors(program, data_chain, indx_err, num_err);
	if (num_reg > 0)
	{
		/* only pass along opt_print() */
		print_reg_paths(data_chain, indx_reg, num_reg);
		if (num_dir > 0)
			printf("\n");
	}
	if (num_dir > 0)
	{
		if ((num_err || num_reg) && (num_dir == 1))
			printf("%s:\n", data_chain[indx_dir[0]]->name);
		/* pass along opt_print() and opt_filter() */
		print_dir_paths(data_chain, indx_dir, num_dir);
	}
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
	/* WORK: take in opt_print func pointer */

	path_data *path;

	for (int r = 0; r < num_reg; r++)
	{
		path = data_chain[indices[r]];

		/* WORK: CALL FUNCTION POINTER */
		printf("%s  ", path->name);
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

	/* take on a filter() and a printer() and then pass the printer to filter
	 * change the pass DIR * to path_data * instead ???
	 */
	while ((dir_item = readdir(dir_stream)))
	{
		char *dir_name = dir_item->d_name;
		/* construct a path_data item for each dir_name ?? */

		/*USE FUNCTION POINTER */
		if (dir_name[0] != '.')
			printf("%s  ", dir_name);
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
	/* take on an opt_filter() and an opt_print() function
	 * then pass them on to print_dir_contents() */

	path_data *path;
	DIR *path_stream;

	for (int d = 0; d < num_dir; d++)
	{
		path = data_chain[indices[d]];
		path_stream = path->stream;

		if (num_dir == 1)
			print_dir_contents(path_stream);
		else
		{
			printf("%s:\n", path->name);
			print_dir_contents(path_stream);
			if ((d + 1) != num_dir)
				printf("\n");
		}
	}
}
