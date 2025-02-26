#include <stdlib.h>
#include <string.h>

char *str_concat(char *prefix, char *suffix)
{
	int len_pre, len_suf, len;
	char *concat;

	len_pre = strlen(prefix);
	len_suf = strlen(suffix);
	len = len_pre + len_suf + 1;

	concat = malloc(sizeof(char) * len);
	memset(concat, 0, len);
	strcpy(concat, prefix);
	strcpy(&(concat[len_pre]), suffix);

	return (concat);
}
