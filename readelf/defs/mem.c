#include <stdlib.h>
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
