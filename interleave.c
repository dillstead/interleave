#include "interleave.h"

#define STACK_SZ     (4096 / sizeof(void *))
static int id;
static void *stack[STACK_SZ] __attribute__ ((aligned (16)));
static void **rsp[2];
void **_switch(void ***cur_esp, void ***next_esp);

static int current(void)
{
    return id;
}

static int next(void)
{
    return ++id % 2;
}

void start(int apply(void *), void *arg)
{
    // Contrive a stack for the call to switch.  The stack needs 
    // to be setup such that once it's swtiched to in switch it will
    // return to apply with arg as the first and only parameter.
    // This stack frame needs to be the exact same size as the frame for
    // switch which has a return address followed by 7 registers.
    stack[STACK_SZ - 1] = *((void **) &apply);
    stack[STACK_SZ - 8] = arg;
    rsp[1] = &stack[STACK_SZ - 8];
}

void yield(void)
{
    int c = current();
    int n = next();
    
    _switch(&rsp[c], &rsp[n]);
}
