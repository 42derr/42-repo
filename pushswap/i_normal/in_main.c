#include "../pushswap.h"

void fix_loop(t_push *push, int o)
{
    if (push->asize > 1 && o != 0)
    {
        o = push->asize % o;
        while (o--)
            cmd_ra(push, 1); 
    }
}

void i_normal_zo_z(t_push *push, int i, int *o)
{
    cmd_pb(push);
    if ((isthere(push, 15 - i, '0') || isthere(push, 15 - i, '1')) 
    && (((push->stacka[push->asize - 1]))[15 - i] == '3' 
    || ((push->stacka[push->asize - 1]))[15 - i] == '2'))
    {
        cmd_rr(push);
        (*o)++;
    }
    else
    {
        if (push->bsize > 0)
            cmd_rb(push, 1);
    }
}

void i_normal_zo(t_push *push, int i)
{
    int o ;
    o = 0;

    while (isthere(push, 15 - i, '0') || isthere(push, 15 - i, '1'))
    {
        if (((push->stacka[push->asize - 1]))[15 - i] == '1')
            cmd_pb(push);
        else if (((push->stacka[push->asize - 1]))[15 - i] == '0')
            i_normal_zo_z(push, i, &o);
        else
        {
            cmd_ra(push, 1);        
            o++;
        }
    }
    fix_loop(push, o);
}

void i_normal(t_push *push, int i)
{
    int o ;

    o = 0;
    i_normal_zo(push, i);
    while (push->asize > 0 && isthere(push, 15 - i, '2'))
    {
        if (((push->stacka[push->asize - 1]))[15 - i] == '2')
            cmd_pb(push);
        else
        {
            o++;
            cmd_ra(push, 1);
        }
    }
    fix_loop(push, o);
}