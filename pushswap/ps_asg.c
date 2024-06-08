#include "pushswap.h"

int    assign_stacka(int argc, char **argv, t_push *push)
{
    int max;
    int i;

    if (check_argv(argc, argv) <= 0)
    {
        if (check_argv(argc, argv) == 0)
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
        push->stacka[max - 1] = atoi(argv[i]);
        max--;
        i++;
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