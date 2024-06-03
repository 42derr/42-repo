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
    while ((**str == '-' || **str == '+' || **str == '#'|| **str == ' ' || **str == '0' || **str == '.' || (**str >= '1' && **str <= '9')) && **str)
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

int	format_length(char *str, va_list args, t_flag *flag)
{
	if (*str == 'c')
   {
      va_arg(args, int);
		return (1);
   }
	else if (*str == 's')
   {
      flag->str = 1;
		return (ft_strlen(va_arg(args, char *), flag));
   }
	else if (*str == 'p')
		return (addr_len(va_arg(args, long)));
	else if (*str == 'd' || *str == 'i')
		return (ft_numlen(va_arg(args, int), flag));
	else if (*str == 'u')
		return (us_len(va_arg(args, unsigned int), flag));
	else if (*str == 'x')
		return (hex_len(va_arg(args, unsigned int), flag));
	else if (*str == 'X')
		return (hex_len(va_arg(args, unsigned int), flag));
	else if (*str == '%')
		return (1);
   return (0);
}

void  len_flag(t_flag *flag, va_list args, char *str)
{
   int len;

   len = 0;
   if ((flag->min || flag->sharp || flag->zero || flag->plus || flag->space || flag->width || flag->dot) && *str != '%' )
      len = format_length(str, args, flag);
   if (flag->min == 1)
   {
      if (flag->dot && flag->dotvalue < len && flag->str)
         flag->back = flag->width - flag->dotvalue;
      else if (flag->dot && flag->dotvalue > len && !flag->str)
      {
            flag->back = flag->width - flag->dotvalue - flag->neg;
      }
      else if (flag->dot && flag->dotvalue < len && !flag->str)
      {
            flag->back = flag->width - len - flag->neg;
      }
      else if (flag->width != 0)
         flag->back = flag->width - len;
   }
   if (flag->zero == 1)
   {
      if (flag->width > len)
            flag->middle = flag->width - len;
   }
   if (flag->width && (!flag->min) && (!flag->sharp) && (!flag->zero) && (!flag->plus))
   {
      if (flag->dot && flag->dotvalue < len && flag->str)
         flag->front = flag->width - flag->dotvalue;
      else if (flag->dot && flag->dotvalue > len && !flag->str)
      {
            flag->front = flag->width - flag->dotvalue - flag->neg;
      }
      else if (flag->dot && flag->dotvalue < len && !flag->str)
      {
            flag->front = flag->width - len - flag->neg;
      }
      else
         flag->front = flag->width - len;
   }
   if (flag->dot && flag->zero)
   {
      if (flag->dotvalue > len)
         flag->front = flag->width - flag->dotvalue - flag->neg;
      else
         flag->front = flag->width - len - flag->neg;
   }
   if (flag->dot)
   {
      if (flag->dotvalue > len && !flag->str)
      {
         flag->middle = flag->dotvalue - len;
         flag->zero = 1;
      }
      else if (flag->dotvalue > len && flag->str)
      {
         flag->middle = len;
      }
      else
      {
         flag->middle = flag->dotvalue;
         flag->zero = 0;
      }
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