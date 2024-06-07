#include "pushswap.h"

int    assign_stacka(int argc, char **argv, t_push *push)
{
    int i;

    if (check_argv(argc, argv) <= 0)
    {
        if (check_argv(argc, argv) == 0)
            printf("Error\n");
        return (0);
    }
    i = argc - 1;
    push->stacka = (int *) malloc(sizeof(int) * (argc - 1));
    if (!push->stacka)
        return (0);
    while (i)
    {
        push->stacka[i - 1] = atoi(argv[i]);
        i--;
    }
    push->asize = argc - 1;
    return (1);
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