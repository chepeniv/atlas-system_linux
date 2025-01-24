#include "hls.h"

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

	printf("%s %lu %s %s %ld %.6s %.4s %s\n",
		read_mode,
		hlinks,
		pw_data->pw_name,
		gr_data->gr_name,
		size,
		read_time,
		&read_time[16],
		name
	);
}

/**
 * process_time - decodes a time_t number into a human-readable time string
 * @time: the unsigned int to interpret
 *
 * Return: the constructed c-string
 */

char *process_time(time_t time)
{
	char *read_time = ctime(&time);

	return (&read_time[4]); /* remove day of the week */
}

/**
 * process_mode - fully decodes an integer into a c-string representing both
 * a file's type and permissions
 * @mode: the integer to process
 *
 * Return: the c-string encoding the type and permission data
 */

char *process_mode(mode_t mode)
{
	char *read_mode = get_perm(mode);

	read_mode[0] = get_type(mode);

	return (read_mode);
}

/**
 * get_perm - decode an integer to extract the permissions data for a file
 * @mode: the integer to
 *
 * Return: a c-string representing all the permissions applicable to a file
 */

char *get_perm(mode_t mode)
{
	static char perm[16];

	/* determine user permissions */
	perm[1] = (S_IRUSR & mode) ? 'r' : '-';
	perm[2] = (S_IWUSR & mode) ? 'w' : '-';
	perm[3] = (S_IXUSR & mode) ? 'x' : '-';

	/* determine group permissions */
	perm[4] = (S_IRGRP & mode) ? 'r' : '-';
	perm[5] = (S_IWGRP & mode) ? 'w' : '-';
	perm[6] = (S_IXGRP & mode) ? 'x' : '-';

	/* determine other permissions */
	perm[7] = (S_IROTH & mode) ? 'r' : '-';
	perm[8] = (S_IWOTH & mode) ? 'w' : '-';
	perm[9] = (S_IXOTH & mode) ? 'x' : '-';

	perm[10] = '\0';

	return (perm);
}

/**
 * get_type - extracts the type information from a integer
 * @mode: the integer to process
 *
 * Return: a character representing the type of file
 */

char get_type(mode_t mode)
{
	if (S_ISREG(mode))  /*regular file */
		return ('-');
	if (S_ISDIR(mode))  /* directory*/
		return ('d');
	if (S_ISCHR(mode))  /* character special */
		return ('c');
	if (S_ISBLK(mode))  /* block special */
		return ('b');
	if (S_ISLNK(mode))  /* link */
		return ('l');
	if (S_ISFIFO(mode)) /* fifo pipe */
		return ('p');
	return ('?');       /* other */
}
