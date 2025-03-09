#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "../libasm.h"

int main(void)
{
    char *src, *dest, *original, *copycat;

    src = strdup("Holberton");
	dest = strdup("......... School");

    for (int i = 0; i <= 9; i++)
    {

        copycat = asm_memcpy(dest, src, i);
        original = memcpy(dest, src, i);
        printf("%s\n", original);
        printf("%s\n", copycat);
    }

	free(dest);
    free(src);

    return (EXIT_SUCCESS);
}
