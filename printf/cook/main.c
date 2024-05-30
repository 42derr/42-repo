#include "printf.h"
#include <stdio.h>

void    flag_min_zero(t_flag *flag, char **str)
{
    int number;

    if (**str == '-')
    {
        while (**str == '-')
           (*str)++;
        number = ft_atoi(*str);
        if (number)
            flag->min = number;
        while (**str >= '0' && **str <= '9')
           (*str)++;
    }
    if (**str == '0')
    {
        while (**str == '0')
           (*str)++;
        number = ft_atoi(*str);
        if (number)
            flag->zero = number;
        while (**str >= '1' && **str <= '9')
           (*str)++;
    }
}

void    flag_plus_space_shrap(t_flag *flag, char **str)
{
    if (**str == '+')
    {
        while (**str == '+')
           (*str)++;
        flag->plus = 1;
    }
    if (**str == ' ')
    {
        while (**str == ' ')
           (*str)++;
        flag->space = 1;
    }
    if (**str == '#')
    {
        while (**str == '#')
           (*str)++;
        flag->sharp = 1;
    }
}

void    flag_width_dot(t_flag *flag, char **str)
{
    int number;

    if (**str >= '1' && **str <= '9')
    {
        number = ft_atoi(*str);
        if (number)
            flag->width = number;
        while (**str >= '0' && **str <= '9')
           (*str)++;
    }
    if (**str == '.')
    {
        while (**str == '.')
           (*str)++;
        number = ft_atoi(*str);
        if (number)
            flag->dot = number;
        while (**str >= '0' && **str <= '9')
           (*str)++;
    }
}

void    flag_loop(t_flag *flag, char **str)
{
    while ((**str == '-' || **str == '+' || **str == '#' || **str == '0' || **str == '.' || **str >= '1' && **str <= '9') && **str)
    {
        if (**str == '-')
           flag_min_zero(flag, str);
        else if (**str == '+')
           flag_plus_space_shrap(flag, str);
        else if (**str == ' ')
           flag_plus_space_shrap(flag, str);
        else if (**str == '#')
           flag_plus_space_shrap(flag, str);
        else if (**str == '0')
           flag_min_zero(flag, str);
        else if (**str >= '1' && **str <= '9')
           flag_width_dot(flag, str);
        else if (**str == '.')
           flag_width_dot(flag, str);
    }
}

void print_flags(t_flag *flag)
{
    printf("plus: %d\n", flag->plus);
    printf("min: %d\n", flag->min);
    printf("space: %d\n", flag->space);
    printf("dot: %d\n", flag->dot);
    printf("sharp: %d\n", flag->sharp);
    printf("width: %d\n", flag->width);
    printf("zero: %d\n", flag->zero);
}

int main(void)
{
    t_flag flag = {0};
    char    *str =  "39-10+ #010.3";

    flag_loop(&flag, &str);
    print_flags(&flag);

    return 0;
}