#include "pushswap.h"

int     check_argv_helper(int argc , char **argv)
{
    int i;
    int j;
    long num;

    i = 1;
    while (i < argc)
    {
        if (argv[i][0] == '-' || argv[i][0] == '+')
            j = 1;
        else
            j = 0;
        if (!argv[i][j])
            return (0);
        while (argv[i][j])
        {
            if (argv[i][j] < '0' || argv[i][j] > '9')
                return (0);
            j++;
        }
        num = ft_atol(argv[i]);
        if (num > 2147483647 || num < -2147483648)
            return (0);
        i++;
    }
    return (1);
}

int    check_argv(int argc, char **argv)
{
    int i;
    int j;

    i = 1;
    while (i < argc - 1)
    {
        j = i + 1;
        while (j < argc)
        {
            if (ft_strcmp(argv[i], argv[j]) == 0)
                 return (0);
            j++;
        }
        i++;
    }
    return (check_argv_helper(argc, argv));
}

int check_stack(t_push *push)
{
    int i;

    i = 0;
    if (push->bsize != 0 || push == NULL || push->astart == NULL)
        return(0);
    while (i < push->asize - 1)
    {
        if (push->astart[i] < push->astart[i + 1])
            return (0);
        i++;
    }
    return (1);
}