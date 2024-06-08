#include "pushswap.h"

int check_stack(t_push *push)
{
    int i;

    i = 0;
    if (push->bsize != 0 || push == NULL || push->stacka == NULL)
        return(0);
    while (i < push->asize - 1)
    {
        if (push->stacka[i] > push->stacka[i + 1])
            return (0);
        i++;
    }
    return (1);
}

int main(int argc, char **argv)
{
    t_push push;

    push = (t_push) {0};
    if (!assign_stacka(argc, argv, &push))
        return (0);
    if (!assign_stackb(argc,&push))
        return (0);

    sort_stacka(&push);
    sort_stacka(&push);

    printf("Sorted stacka:\n");
    for (int i = 7; i >= 0; i--)
    {
        printf("%d\n", push.stacka[i]);
    }

    return 0;
}