#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "../signals.h"

int main(void)
{
    int i;

    if (handle_signal() == -1)
    {
        printf("Failure\n");
        return (EXIT_FAILURE);
    }
    for (i = 0; ; i++)
    {
        printf("[%d] Wait for it ...\n", i);
        sleep(1);
    }
    return (EXIT_SUCCESS);
}
