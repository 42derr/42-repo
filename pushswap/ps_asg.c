#include "pushswap.h"

int    assign_stacka(int argc, char **argv, t_push *push)
{
    int max;
    int i;

    if (check_argv(argc, argv) == 0)
    {
        printf("Error\n");
        return (0);
    }
    max = argc - 1;
    i = 1;
    push->stacka = (int *) malloc(sizeof(int) * (argc - 1));
    if (!push->stacka)
        return (0);
    while (max)
    {
        push->stacka[max - 1] = atol(argv[i]);
        max--;
        i++;
    }
    push->asize = argc - 1;
    reassign_stacka(push);
    return (1);
}

void   reassign_stacka(t_push *push)
{
    int i;
    int j;
    int c;
    int *newstack;
    
    newstack = (int *) malloc(sizeof(int) * push->asize);
    if (!newstack)
        return ;
    i = 0;
    while (i < push->asize)
    {
        j = 0;
        c = 0;
        while (j < push->asize)
        {
            if (push->stacka[i] > push->stacka[j])
                c++;
            j++;
        }
        newstack[i] = c;
        i++;
    }
    free(push->stacka);
    push->stacka = newstack;
}

int    assign_stackb(int argc, t_push *push)
{
    push->stackb = (int *) malloc(sizeof(int) * (argc - 1));
    if (!push->stackb)
    {
        free(push->stacka);
        return (0);
    }
    push->bsize = 0;
    return (1);
}