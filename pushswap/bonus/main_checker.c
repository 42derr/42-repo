#include "../pushswap.h"

int do_cmd(char *str, t_push *push)
{
    if (ft_strcmp(str,"sa\n") == 0)
        checker_sa(push);
    else if (ft_strcmp(str,"sb\n") == 0)
        checker_sb(push);
    else if (ft_strcmp(str,"ss\n") == 0)
        checker_ss(push);
    else if (ft_strcmp(str,"ra\n") == 0)
        checker_ra(push);
    else if (ft_strcmp(str,"rb\n") == 0)
        checker_rb(push);
    else if (ft_strcmp(str,"rr\n") == 0)
        checker_rr(push);
    else if (ft_strcmp(str,"rra\n") == 0)
        checker_rra(push);
    else if (ft_strcmp(str,"rrb\n") == 0)
        checker_rrb(push);
    else if (ft_strcmp(str,"rrr\n") == 0)
        checker_rrr(push);
    else if (ft_strcmp(str,"pa\n") == 0)
        checker_pa(push);
    else if (ft_strcmp(str,"pb\n") == 0)
        checker_pb(push);
    else
        return (0);
    return (1);
}

void check_sort(t_push *push)
{
    int i;

    i = 0;
    while (i < push->asize - 1)
    {
        if (push->astart[i] < push->astart[i + 1])
        {
            ft_putstr_fd("KO\n", 1);
            return ;
        }
        i++;
    }
    ft_putstr_fd("OK\n", 1);
}

int main(int argc, char **argv)
{
    t_push push;
    char    *cmd;

    push = (t_push) {0};
    if (!assign_stacka(argc, argv, &push))
        return (0);
    if (!assign_stackb(argc,&push))
        return (0);
    if (check_stack(&push) || argc == 2)
    {
        free(push.astart);
        free(push.bstart);
        return (0);
    }
    while ((cmd = get_next_line(0)) != NULL)
    {
        if (!do_cmd(cmd, &push))
        {
            ft_putstr_fd("Error\n", 2);
            return (0);
        }
        free(cmd);
    }
    check_sort(&push);
    return (0);
}