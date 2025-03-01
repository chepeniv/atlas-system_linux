#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/**
 * mem_alloc - allocate and properly initialize data buffer given
 * @buff: the address of the pointer to which to attach the buffer
 * @size: the total bytes to allocate
 *
 * Return: 0
 */
int mem_alloc(void **buff, int size, int len)
{
	*buff = malloc(size * len);
	memset(*buff, 0, len * size);

	return (0);
}

int nullify(void **series, int len)
{
	for (int i = 0; i < len; i++)
		series[i] = NULL;

	return (0);
}

char *setup_str_mem(char *text, int len)
{
	char *mailback;

	mem_alloc((void **) &mailback, sizeof(char), len);
	sprintf(mailback, "%s", text);

	return (mailback);
}

void free_text_array(char **text)
{
	for (int i = 0; text[i]; i++)
		free(text[i]);
	free(text);
}
