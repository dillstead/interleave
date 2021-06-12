// gcc -Wall -Werror -Wno-format -pedantic -std=c99 -g3 -o interleave _switch.S interleave.c main.c
#include <stdlib.h>
#include <stdio.h>
#include "interleave.h"

int work(void *name)
{
    int i = 0;
    
    printf("%s %d\n", name, i++);
    yield();
    printf("%s %d\n", name, i++);
    yield();
    printf("%s %d\n", name, i++);
    yield();
    return 0;
}


int main(void)
{
    
    start(work, "secondary");
    work("primary");
    return EXIT_SUCCESS;
}
