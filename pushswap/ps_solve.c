#include "pushswap.h"

void    solve_stack_3num(t_push *push)
{
    if (push->astart[0] == 1 && push->astart[1] == 2 && push->astart[2] == 0)
    {
        cmd_sa(push, 1);
        cmd_ra(push, 1);
    }
    else if (push->astart[0] == 2 && push->astart[1] == 0 && push->astart[2] == 1)
        cmd_sa(push, 1);
    else if (push->astart[0] == 0 && push->astart[1] == 2 && push->astart[2] == 1)
        cmd_rra(push, 1);
    else if (push->astart[0] == 1 && push->astart[1] == 0 && push->astart[2] == 2)
        cmd_ra(push, 1);
    else if (push->astart[0] == 0 && push->astart[1] == 1 && push->astart[2] == 2)
    {
        cmd_sa(push, 1);
        cmd_rra(push, 1);
    }
}

void    solve_stack_4num(t_push *push)
{
    if (push->astart[2] == 3)
        cmd_sa(push, 1);
    else if (push->astart[1] == 3)
    {
        cmd_ra(push, 1);
        cmd_sa(push, 1);
    }
    else if (push->astart[0] == 3)
        cmd_rra(push, 1);
    cmd_pb(push);
    solve_stack_3num(push);
    cmd_pa(push);
    cmd_ra(push, 1);
}

void    solve_stack_5num(t_push *push)
{
    if (push->astart[3] == 4)
        cmd_sa(push, 1);
    else if (push->astart[2] == 4)
    {
        cmd_ra(push, 1);
        cmd_sa(push, 1);
    }
    else if (push->astart[1] == 4)
    {
        cmd_rra(push, 1);
        cmd_rra(push, 1);
    }
    else if (push->astart[0] == 4)
        cmd_rra(push, 1);
    cmd_pb(push);
    solve_stack_4num(push);
    cmd_pa(push);
    cmd_ra(push, 1);
}

void    solve_stack(t_push *push, int argc)
{
    if (argc == 3 && push->astart[0] < push->astart[1])
        printf("sa");
    if (argc == 4)
        solve_stack_3num(push);
    if (argc == 5)
        solve_stack_4num(push);
    if (argc > 5)
        radix_base4(push);
}