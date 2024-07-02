#include "../pushswap.h"

void ils_finish(t_push *push, int i)
{
    while (push->bsize > 0 && isthereb(push, 15 - i, '0'))
    {
        if (((push->stackb[push->bsize - 1]))[15 - i] == '0')
            cmd_pa(push);
        if (((push->stackb[push->bsize - 1]))[15 - (i - 1)] == '0')
            break ;
    }
    while (push->bsize > 0)
    {
        if (push->bsize > 1)
        {
            cmd_rrb(push, 1);
            cmd_pa(push);
        }
        else
            cmd_pa(push);
    }
}

void i_last_spes(t_push *push, int i, int max)
{
    int hun;
    int o;

    i++;
    hun = 0;
    o = 0;
    ils_start(push, i, &hun);
    ils_one(push, i, &hun, max);
    ils_zero(push, i, &o);
    ils_adjust(push, o, hun);
    ils_finish(push, i);
    free(push->stacka);
    free(push->stackb);
    exit(0);
}