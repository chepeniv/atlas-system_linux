#include "hls.h"
#include <time.h>

/******** OPTIONS ********/

/******** OPTION FILTERS ********/

/* print all none . files */
void opt_standard_filter(
void (*print)(path_data *),
path_data *path)
{
	char *name = path->name;

	if (name[0] != '.')
		print(path);
}

/* print all files including .-hidden files */
void opt_all_filter(
void (*print)(path_data *),
path_data *path)
{
	print(path);
}

/* print every file except ./ ../ */
void opt_almost_all_filter(
void (*print)(path_data *),
path_data *path)
{
	char *name = path->name;

	if (name[0] == '.')
	{
		if (name[1] != '.' &&
			name[1] != '\0')
			print(path);
	}
	else
		print(path);

}

/******** OPTION PRINTERS ********/

void opt_standard_print(path_data *path)
{
	printf("%s  ", path->name);
}

void opt_column_print(path_data *path)
{
	printf("%s\n", path->name);
}

/* move to it's own file with its own functions */
void opt_long_print(path_data *path)
{
	/* print details in single column
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

	struct stat *path_stat = path->stat;
	char    *name     = path->name;

	mode_t   mode     = path_stat->st_mode;   /* int */
	nlink_t  hlinks   = path_stat->st_nlink;  /* long unsigned int */
	uid_t    user_id  = path_stat->st_uid;    /* int */
	gid_t    group_id = path_stat->st_gid;    /* int */
	off_t    size     = path_stat->st_size;   /* long unsigned int */
	time_t   mtime    = path_stat->st_mtime;  /* long unsigned int */

	/* process mode */
	/* process user_id */
	/* process group_id */
	/* process mtime */

	printf("%d %lu %d %d %ld %ld %s\n", /* determined types */
		mode,
		hlinks,
		user_id,
		group_id,
		size,
		mtime,
		name
	);
}
