#ifndef PRINT_H
# define PRINT_H

typedef struct s_flag
{
    int plus;
    int min;
    int space;
    int dot;
    int sharp;
    int width;
    int zero;
} t_flag;

int		ft_atoi(const char *nptr);

#endif