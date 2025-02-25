#include <stdlib.h>
#include <string.h>

/**
 * mem_alloc - allocate and properly initialize data buffer given
 * @buff: the address of the pointer to which to attach the buffer
 * @size: the total bytes to allocate
 *
 * Return: 0
 */
int mem_alloc(char **buff, int size)
{
	*buff = malloc(sizeof(char) * size);
	memset(*buff, 0, size);

	return (0);
}
