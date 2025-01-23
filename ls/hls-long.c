#include "hls.h"

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

	/* determine all permissions */
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
