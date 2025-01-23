#include "hls.h"

/******** OPTIONS ********/

/******** OPTION FILTERS ********/

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

/******** OPTION PRINTERS ********/

/**
 * opt_column_print - option for outputting all items into a single column
 * @path: the struct to process for output
 */

void opt_column_print(path_data *path)
{
	printf("%s\n", path->name);
}

/*
 * print details in single column
 *
 * the following information in documented in
 * `man 3 stat`
 * `info ls` (section: 10.1.2 What Information is Listed)
 *
 * type       hardlinks
 * |mode      | owner group  size time         name
 * ||________ | |____ |____  |___ |___________ |________
 * -rw-rw-r-- 1 chepe chepe  1928 Jan 17 14:22 README.md
 *
 * struct stat
 *    mode_t  st_mode  -> type and mode
 *    nlink_t st_nlink -> number of hardlinks
 *    uid_t   st_uid   -> single owner id (name has to be extracted)
 *    gid_t   st_gid   -> group owner id (name has to be extracted)
 *    off_t   st_size  -> size of file
 *    struct timespec
 *            st_mtim  -> time of last modification
 */

/**
 * opt_long_print - the most detailed output formatting option
 * @path: the struct to analyze and extract data from for output
 */

void opt_long_print(path_data *path)
{
	struct stat *path_stat = path->stat;
	char    *name     = path->name;

	mode_t   mode     = path_stat->st_mode;   /* int */
	nlink_t  hlinks   = path_stat->st_nlink;  /* long unsigned int */
	uid_t    u_id     = path_stat->st_uid;    /* int */
	gid_t    gr_id    = path_stat->st_gid;    /* int */
	off_t    size     = path_stat->st_size;   /* long unsigned int */
	time_t   mtime    = path_stat->st_mtime;  /* long unsigned int */

	char *read_mode = process_mode(mode);
	char *read_time = process_time(mtime);
	struct passwd *pw_data = getpwuid(u_id);
	struct group *gr_data = getgrgid(gr_id);

	printf("%s %lu %s %s %ld %s %s\n",
		read_mode,
		hlinks,
		pw_data->pw_name,
		gr_data->gr_name,
		size,
		read_time,
		name
	);
}
