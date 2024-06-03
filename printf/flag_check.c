#include "libft/libft.h"
#include "ft_printf.h"

void    flag_loop_helper(int *value, char **str)
{
      if (**str == '.')
         (*str)++;
      *value = ft_atoi(*str);
      while (**str >= '0' && **str <= '9')
         (*str)++;
}

void    flag_loop(t_flag *flag, char **str)
{
    while ((**str == '-' || **str == '+' || **str == '#'|| **str == ' ' 
    || **str == '0' || **str == '.' || (**str >= '1' && **str <= '9')) && **str)
    {
        if (**str == '-')
           flag->min = 1;
        else if (**str == '+')
            flag->plus = 1;
        else if (**str == ' ')
           flag->space = 1;
        else if (**str == '#')
           flag->sharp = 1;
        else if (**str == '0')
           flag->zero = 1;
        else if (**str == '.')
        {
            flag->dot = 1;
            flag_loop_helper(&(flag->dotvalue), str);
        }
        else if (**str >= '1' && **str <= '9')
            flag_loop_helper(&(flag->width), str);
         if (**str == '-' || **str == '+' || **str == '#' || **str == '0' || **str == ' ')
            (*str)++;
    }
}

void  clear_flag (t_flag *flag)
{
    flag->plus = 0;
    flag->min = 0;
    flag->space = 0;
    flag->dot = 0;
    flag->sharp = 0;
    flag->width = 0;
    flag->zero = 0;
    flag->front = 0;
    flag->middle = 0;
    flag->dotvalue = 0;
    flag->back = 0;
    flag->str = 0;
    flag->neg = 0;
}