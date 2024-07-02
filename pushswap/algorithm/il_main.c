#include "../pushswap.h"

void ils_start(t_push *push , int i, int *hun)
{   
    int o;

    o = 0;
    if (!isthere(push, 15 - i, '1'))
        *hun = push->asize;
    while (push->asize > 0 && isthere(push, 15 - i, '0') && *hun == 0)
    {
        if (((push->stacka[push->asize - 1]))[15 - i] == '0')
            cmd_pb(push);
        else
        {
            o++;
            cmd_ra(push, 1);
        }
    }
    fix_loop(push, o);
}

void ils_one(t_push *push , int i, int *hun, int max)
{   
    if (max < 5)
    {
        while(push->bsize > 0 && ((push->stackb[push->bsize - 1]))[15 - i] == '0')
        {
            cmd_pa(push);
            (*hun)++;
        }
    }
    while (push->bsize > 0 && isthereb(push, 15 - i, '1'))
    {
        if (((push->stackb[push->bsize - 1]))[15 - (i - 1)] == '0')
            break ;
        if (((push->stackb[push->bsize - 1]))[15 - i] == '1')
            cmd_pa(push);
        else
            cmd_rb(push, 1);
    }
}

void ils_zero(t_push *push , int i, int *o)
{   
    while (push->bsize > 0 && ((push->stackb[push->bsize - 1]))[15 - (i - 1)] == '0')
    {
        if (((push->stackb[push->bsize - 1]))[15 - i] == '1')
        {
            cmd_pa(push);
            if (((push->stackb[push->bsize - 1]))[15 - i] == '1')
            {
                cmd_ra(push, 1);
                (*o)++;
            }
            else
            {
                if (!(((push->stackb[push->bsize - 1]))[15 - (i - 1)] == '0'))
                    break ;
                cmd_rr(push);
                (*o)++;
            }
        }
        else
            cmd_rb(push, 1);
    }
}


void ils_adjust(t_push *push , int o, int hun)
{   
    if (push->asize - (o + hun) > (o + hun))
    {
        while(o--)
            cmd_rra(push, 1);
        while (hun--)
            cmd_rra(push, 1);
    }
    else
    {
        o = push->asize - o - hun;
        while(o--)
            cmd_ra(push,1);
    }
}