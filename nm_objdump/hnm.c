#include <unistd.h>
#include <stdio.h>

int main(int count, char **args)
{
	for (int i = 1; i < count; i++)
		printf("[%d] %s\n", i, args[i]);

	return (0);
}
