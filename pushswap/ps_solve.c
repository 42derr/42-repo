#include "pushswap.h"

void    solve_stack_3num(t_push *push)
{
    if (push->astart[0] == 1 && push->astart[1] == 2 && push->astart[2] == 0)
    {
        ft_putstr_fd("sa\n", 1);
        ft_putstr_fd("ra\n", 1);
    }
    else if (push->astart[0] == 2 && push->astart[1] == 0 && push->astart[2] == 1)
        ft_putstr_fd("sa\n", 1);
    else if (push->astart[0] == 0 && push->astart[1] == 2 && push->astart[2] == 1)
        ft_putstr_fd("rra\n", 1);
    else if (push->astart[0] == 1 && push->astart[1] == 0 && push->astart[2] == 2)
        ft_putstr_fd("ra\n", 1);
    else if (push->astart[0] == 0 && push->astart[1] == 1 && push->astart[2] == 2)
    {
        ft_putstr_fd("sa\n", 1);
        ft_putstr_fd("rra\n", 1);
    }
}

void    solve_stack_4num(t_push *push)
{
    if (push->astart[2] == 3)
    {
        checker_sa(push);
        ft_putstr_fd("sa\n", 1);
    }
    else if (push->astart[1] == 3)
    {
        ft_putstr_fd("ra\n", 1);
        checker_ra(push);
        ft_putstr_fd("sa\n", 1);
        checker_sa(push);
    }
    else if (push->astart[0] == 3)
    {
        ft_putstr_fd("rra\n", 1);
        checker_rra(push);
    }
    ft_putstr_fd("pb\n", 1);
    checker_pb(push);
    solve_stack_3num(push);
    ft_putstr_fd("pa\n", 1);
    ft_putstr_fd("ra\n", 1);
}

void    solve_stack_5num(t_push *push)
{
    if (push->astart[3] == 4)
    {
        ft_putstr_fd("sa\n", 1);
        checker_sa(push);
    }
    else if (push->astart[2] == 4)
    {
        ft_putstr_fd("ra\n", 1);
        checker_ra(push);
        ft_putstr_fd("sa\n", 1);
        checker_sa(push);
    }
    else if (push->astart[1] == 4)
    {
        ft_putstr_fd("rra\n", 1);
        checker_rra(push);
        ft_putstr_fd("rra\n", 1);
        checker_rra(push);
    }
    else if (push->astart[0] == 4)
    {
        ft_putstr_fd("rra\n", 1);
        checker_rra(push);
    }
    ft_putstr_fd("pb\n", 1);
    checker_pb(push);
    solve_stack_4num(push);
    ft_putstr_fd("pa\n", 1);
    ft_putstr_fd("ra\n", 1);
}

void    solve_stack(t_push *push, int argc)
{
    if (argc == 3 && push->astart[0] < push->astart[1])
        ft_putstr_fd("sa\n",1);
    else if (argc == 4)
        solve_stack_3num(push);
    else if (argc == 5)
        solve_stack_4num(push);
    else if (argc == 6)
        solve_stack_5num(push);
    if (argc > 6)
        radix_base4(push);
}