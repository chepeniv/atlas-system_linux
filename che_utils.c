#include <stdlib.h>

/* definitions of commonly useful functions */

int string_length(const char *string)
{
	int length = 0;

	while (string[length] != '\0')
		length++;

	return (length);
}

char *copy_string(char *buffer, char *string, int length)
{
	int pos = 0;

	if (length < 0)
		length = string_length(string);

	while (string[pos] != '\0' && pos < length)
	{
		buffer[pos] = string[pos];
		pos++;
	}

	buffer[pos++] = '\0';
	return (buffer);
}

char *concat_string(char *prefix, char *suffix, int range)
{
	int length = string_length(prefix);
	char *concat = malloc(sizeof(char) *(length + range));

	concat = copy_string(concat, prefix, -1);
	concat = copy_string(&concat[length], suffix, range);

	return (concat);
}

/*remove duplicates*/

/*memset*/
