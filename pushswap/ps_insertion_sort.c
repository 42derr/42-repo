#include "pushswap.h"

int find_loc(t_push *push, int num)
{
    int i;

    i = 0;
    while (i < push->asize)
    {
        if (push->stacka[i] == num)
            return (push->asize - 1 - i);
        i++;
    }
    return (0);
}

void    insertion_sort(t_push *push)
{
    int n;
    int i;
    int loc;

    n = push->asize;
    i = 0;
    while (i < n - 1)
    {
        loc = find_loc(push, i);
        if (loc > (push->asize / 2))
        {
            loc = push->asize - loc;
            while (loc--)
                cmd_rra (push, 1);
        }
        else
            while (loc--)
                cmd_ra (push, 1);
        cmd_pb(push);
        i++;
    }
    while (push->bsize)
        cmd_pa(push);
}