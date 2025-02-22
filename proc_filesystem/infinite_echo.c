#include <stdio.h>
#include <unistd.h>

int main(int c, char **argv)
{
	if (c < 2)
	{
		printf("usage: ./inf_echo \"string\"\n");
		return (1);
	}

	while (1)
	{
		printf("%s\n", argv[1]);
		sleep(2);
	}

	return(0);
}
