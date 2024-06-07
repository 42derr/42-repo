#include "pushswap.h"

int     check_argv_helper(int argc , char **argv)
{
    int i;
    int j;

    i = 1;
    while (i < argc)
    {
        if (argv[i][0] == '-' || argv[i][0] == '+')
            j = 1;
        else
            j = 0;
        while (argv[i][j])
        {
            if (argv[i][j] < '0' || argv[i][j] > '9')
                return (0);
            j++;
        }
        long num = atol(argv[i]);
        if (num > INT_MAX || num < INT_MIN)
            return (0);
        i++;
    }
    if (argc < 3)
        return (-1);
    return (1);
}

int    check_argv(int argc, char **argv)
{
    int i;
    int j;

    i = 1;
    while (i < argc)
    {
        j = i + 1;
        while (j < argc)
        {
            if (strcmp(argv[i], argv[j]) == 0)
                 return (0);
            j++;
        }
        i++;
    }
    return (check_argv_helper(argc, argv));
}