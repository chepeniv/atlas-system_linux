#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "../libasm.h"

int main(void)
{
    int i;
    char *src, *dest;

    src = strdup("Holberton");

    for (i = 0; i <= 9; i++)
    {
        dest = strdup("......... School");

        assert(asm_memcpy(dest, src, i) == dest);
        printf("%s\n", dest);
        free(dest);
    }
    free(src);

    return (EXIT_SUCCESS);
}
