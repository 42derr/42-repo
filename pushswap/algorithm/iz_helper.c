#include "../pushswap.h"

void    i_zero(t_push *push, int *i)
{
    (*i)++;
    iz_first(push, *i);
    if (push->asize != 0)
        iz_second(push, *i);
}

int     iz_check_top(t_push *push, int i, int cf, int ct)
{
    if ((((push->stacka[push->asize - 1]))[15 - i] == cf 
    && ((push->stacka[push->asize - 1]))[15 - (i - 1)] == ct))
        return (1);
    else
        return (0);
}

int     iz_check_topb(t_push *push, int i, int cf, int ct)
{
    if ((((push->stackb[push->bsize - 1]))[15 - i] == cf 
    && ((push->stackb[push->bsize - 1]))[15 - (i - 1)] == ct))
        return (1);
    else
        return (0);
}

int     iz_check_botb(t_push *push, int i, int cf, int ct)
{
    if ((((push->stackb[0]))[15 - i] == cf 
    && ((push->stackb[0]))[15 - (i - 1)] == ct))
        return (1);
    else
        return (0);
}

int     iz_break(t_push *push, int cf, int ct, int is)
{
    int i;

    i = 0;
    while (i < push->asize)
    {
        if ((push->stacka[i])[15 - is] == cf && (push->stacka[i])[15 - (is - 1)] == ct)
            return (1);
        i++;
    }
    return (0);
}