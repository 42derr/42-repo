#include "../pushswap.h"

void iz_first_zero(t_push *push , int i)
{
    if(((push->stacka[push->asize - 1]))[15 - (i - 1)] == '3')
    {
        cmd_pb(push);
    }
    else
    {
        cmd_pb(push);
        if ((((push->stacka[push->asize - 1]))[15 - i] == '2' 
        || iz_check_top(push, i, '3', '1')
        || iz_check_top(push, i, '3', '0')
        || iz_check_top(push, i, '1', '2')
        || iz_check_top(push, i, '1', '3')
        ))
        {
            cmd_rr(push);
        }
        else
        {
            cmd_rb(push, 1);
        }
    }
}

void iz_first_three(t_push *push , int i)
{
    if (((push->stacka[push->asize - 1]))[15 - (i - 1)] == '3')
    {
        cmd_pb(push);
        if ((((push->stacka[push->asize - 1]))[15 - i] == '2' 
        || iz_check_top(push, i, '3', '1')
        || iz_check_top(push, i, '3', '0')
        || iz_check_top(push, i, '1', '2')
        || iz_check_top(push, i, '1', '3')
        ))
            cmd_rr(push);
        else
            cmd_rb(push, 1);
    }
    else if (((push->stacka[push->asize - 1]))[15 - (i - 1)] == '2')
    {
        cmd_pb(push);
    }
    else
    {
        cmd_ra(push ,1);
    }
}

void iz_first(t_push *push, int i)
{
    while (1)
    {
        if (iz_check_top(push, i, '1', '0') || iz_check_top(push, i, '1', '1'))
                cmd_pb(push);
        else if (((push->stacka[push->asize - 1]))[15 - i] == '0')
            iz_first_zero(push, i);
        else if (((push->stacka[push->asize - 1]))[15 - i] == '3')
            iz_first_three(push , i);
        else
                cmd_ra(push, 1);        
        if (!iz_break(push, '3', '3', i) 
        && !iz_break(push, '3', '2', i)
        && !iz_break(push, '1', '1', i)
        && !iz_break(push, '1', '0', i)
        && !iz_break(push, '0', '3', i)
        && !iz_break(push, '0', '2', i)
        && !iz_break(push, '0', '1', i)
        && !iz_break(push, '0', '0', i))
            break;
    }
}

void iz_second_one(t_push *push , int i)
{
    if(((push->stacka[push->asize - 1]))[15 - (i - 1)] == '3')
    {
        cmd_pb(push);
        if (iz_check_top(push, i, '3', '0')
        || iz_check_top(push, i, '2', '2')
        || iz_check_top(push, i, '2', '1')
        || iz_check_top(push, i, '2', '3')
        )
        {
            cmd_rr(push);
        }
        else
        {
            cmd_rb(push, 1);
        }
    }
    else
    {
        cmd_pb(push);
    }
}


void iz_second(t_push *push, int i)
{
    while (1)
    {
        if (((push->stacka[push->asize - 1]))[15 - i] == '1')
            iz_second_one(push , i);
        else if (iz_check_top(push, i, '2', '0'))
                cmd_pb(push);
        else if (iz_check_top(push, i, '3', '1'))
                cmd_pb(push);
        else
                cmd_ra(push, 1);        
        if (!iz_break(push, '1', '2', i) 
        && !iz_break(push, '1', '3', i)
        && !iz_break(push, '2', '0', i)
        && !iz_break(push, '3', '1', i))
            break;  
    }
}