#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main(int c, char **argv)
{
	char *echo_txt;
	int len;

	if (c < 2)
	{
		printf("usage: ./inf_echo \"string\"\n");
		return (1);
	}

	len = strlen(argv[1]);
	echo_txt = malloc(sizeof(char) * len);
	strcpy(echo_txt, argv[1]);

	while (1)
	{
		printf("%s\n", echo_txt);
		sleep(2);
	}

	free(echo_txt);

	return(0);
}
