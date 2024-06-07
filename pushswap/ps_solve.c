#include "pushswap.h"

int stacka_sorted(t_push *push)
{
    int i;

    i = 0;
    if (push == NULL || push->stacka == NULL)
        return(0);
    while (i < push->asize - 1  && push->asize > 1)
    {
        if (push->stacka[i] > push->stacka[i + 1])
            return (0);
        i++;
    }
    return (1);
}

int stackb_sorted(t_push *push)
{
    int i;

    i = 0;
    if (push == NULL || push->stackb == NULL)
        return(0);
    while (i < push->bsize - 1 && push->bsize > 1)
    {
        if (push->stackb[i] < push->stackb[i + 1])
            return (0);
        i++;
    }
    return (1);
}

void    sort_stacka(t_push *push)
{
    int pivot;

    if (stacka_sorted(push))
    {
        sort_stackb(push);
    }
    else
    {
        while (1)
        {
            if (push->stacka[0] > push->stacka[push->asize - 1] && push->stacka[0] > push->stacka[push->asize - 2])
                cmd_rra(push, 1);
            else if (push->stacka[push->asize - 2] > push->stacka[push->asize - 1] && push->stacka[push->asize - 2] > push->stacka[0])
                cmd_sa(push, 1);
            else
                break ;
        }
        pivot = push->stacka[push->asize - 1];
        cmd_pb(push);
        while (1)
        {
            if (push->stacka[push->asize - 1] < pivot)
                cmd_pb(push);
            else if (push->stacka[push->asize - 2] < pivot || push->stacka[0] < pivot)
            {
                if (push->stacka[push->asize - 2] > push->stacka[0])
                    cmd_sa(push, 1);
                else
                    cmd_rra(push, 1);
                cmd_pb(push);
            }
            else
                break ;
        }
        sort_stackb(push);
    }
}

void    sort_stackb(t_push *push)
{
    int pivot;

    if (stackb_sorted(push))
    {
        sort_stacka(push);
    }
    else
    {
        while (1)
        {
            if (push->stackb[0] < push->stackb[push->bsize - 1] && push->stackb[0] < push->stackb[push->bsize - 2])
                cmd_rrb(push, 1);
            else if (push->stackb[push->bsize - 2] < push->stackb[push->bsize - 1] && push->stackb[push->bsize - 2] < push->stackb[0])
                cmd_sb(push, 1);
            else
                break ;
        }
        pivot = push->stackb[push->bsize - 1];
        cmd_pa(push);
        while (1)
        {
            if (push->stackb[push->bsize - 1] < pivot)
                cmd_pb(push);
            else if (push->stackb[push->bsize - 2] > pivot || push->stackb[0] > pivot)
            {
                if (push->stackb[push->bsize - 2] < push->stackb[0])
                    cmd_sb(push, 1);
                else
                    cmd_rrb(push, 1);
                cmd_pa(push);
            }
            else
                break ;
        }
        sort_stacka(push);
    }
}