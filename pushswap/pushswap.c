#include "pushswap.h"

int main(int argc, char **argv)
{
    t_push push;

    push = (t_push) {0};
    if (argc == 1)
        return (0);
    if (!assign_stacka(argc, argv, &push))
        return (0);
    if (!assign_stackb(argc,&push))
        return (0);
    if (check_stack(&push))
    {
        free(push.astart);
        free(push.bstart);
        return (0);
    }
    solve_stack(&push, argc);
    free(push.astart);
    free(push.bstart);
    return (0);
}