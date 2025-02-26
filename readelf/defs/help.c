#include "../headers/help.h"
#include "../headers/const.h"
#include "../headers/mem.h"

#include <fcntl.h> /* O_* defs */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

/**
 * print_help - prints readelf help text to stdout
 *
 * Return: 0
 */
int print_help(void)
{
	const char *filename = "assets/readelf-help.txt";
	int fdesc;
	char *text;

	fdesc = open(filename, O_RDONLY);
	mem_alloc(&text, FILE_BUFF_SIZE);
	read(fdesc, text, FILE_BUFF_SIZE);
	close(fdesc);

	printf("%s", text);

	free(text);

	return (0);
}
