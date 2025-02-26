#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "../headers/err.h"
#include "../headers/help.h"

/*
 * //// ERRORS ////
 *
 * "readelf: Warning: Nothing to do.\n[readelf --help]" (no file given)
 * "readelf: Error: 'doesntexist': No such file"
 * "readelf: Error: Input file 'noread' is not readable"
 * "readelf: Error: Not an ELF file - it has the wrong magic bytes at the start"
 */

int err_print(char *procname, char *item)
{
	switch (errno)
	{
	case (W_NOARG):
		dprintf(STDERR_FILENO, "%s: Warning: Nothing to do.\n", procname);
		print_help();
		break;
	case (E_NELF):
		dprintf(
			STDERR_FILENO,
"%s: Error: Not an ELF file - it has the wrong magic bytes at the start\n",
			procname);
		break;
	case (ENOENT):
		dprintf(
			STDERR_FILENO,
			"%s: Error: '%s': No such file\n",
			procname, item);
		break;
	case (EACCES):
		dprintf(
			STDERR_FILENO,
			"%s: Error: Input file '%s' is not readable\n",
			procname, item);
		break;
	}

	exit(EXIT_FAILURE);

	return (errno);
}
