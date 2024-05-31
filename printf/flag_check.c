#include "ft_printf.h"

void    flag_loop(t_flag *flag, char **str)
{
   if (**str == '%')
      (*str)++;
    while ((**str == '-' || **str == '+' || **str == '#' || **str == '0' || **str == '.' || **str >= '1' && **str <= '9') && **str)
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
           flag->sharp = 1;
        else if (**str >= '1' && **str <= '9')
        {
            flag->width = ft_atoi(&str);
            while (**str >= '1' && **str <= '9')
               (*str)++;
        }
        else if (**str == '.')
        {
            (*str)++;
            flag->dot = ft_atoi(&str);
            while (**str >= '1' && **str <= '9')
               (*str)++;
        }
      (*str)++;
    }
}

int	format_length(char *str, va_list args)
{
	if (*str == 'c')
		return (1);
	else if (*str == 's')
		return (ft_strlen(va_arg(args, char *)));
	else if (*str == 'p')
		return (addr_len(va_arg(args, long)));
	else if (*str == 'd')
		return (ft_numlen(va_arg(args, int)));
	else if (*str == 'i')
		return (ft_numlen(va_arg(args, int)));
	else if (*str == 'u')
		return (us_len(va_arg(args, unsigned int)));
	else if (*str == 'x')
		return (hex_len(va_arg(args, unsigned int)));
	else if (*str == 'X')
		return (hex_len(va_arg(args, unsigned int)));
	else if (*str == '%')
		return (1);
}

void  len_flag(t_flag *flag)
{
   if (flag->min == 1)
   {
      
   }
}