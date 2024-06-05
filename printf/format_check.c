/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfasius <dfasius@student.42.sg>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 15:51:07 by dfasius           #+#    #+#             */
/*   Updated: 2024/05/22 16:41:54 by dfasius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft/libft.h"
#include "ft_printf.h"

void	format_check(char *str, va_list args, int *i, t_flag *flag)
{
	while (flag->front-- && flag->front >= 0 && !(*str == '%'))
		ft_putchar(' ', i);
	if (*str == 'c')
		ft_putchar (va_arg(args, int), i);
	else if (*str == 's')
		ft_putstr (va_arg(args, char *), i, flag);
	else if (*str == 'p')
		ft_put_addr (va_arg(args, void *), i);
	else if (*str == 'd' || *str == 'i')
		ft_putnbr_helper (va_arg(args, int), i, flag);
	else if (*str == 'u')
		ft_put_us_num (va_arg(args, unsigned int), i,flag);
	else if (*str == 'x')
		ft_put_small_hex (va_arg(args, unsigned int), i, flag);
	else if (*str == 'X')
		ft_put_big_hex (va_arg(args, unsigned int), i, flag);
	else if (*str == '%')
		ft_putchar('%', i);
	while (flag->back-- && flag->back >= 0 && !(*str == '%'))
	{
		ft_putchar(' ', i);
	}
}

void len_flag_dot(t_flag *flag, int len)
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

void len_flag_width(t_flag *flag, int len)
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


void len_flag_min(t_flag *flag, int len)
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

void  len_flag(t_flag *flag, va_list args, char *str)
{
   int len;

   len = 0;
   if ((flag->min || flag->sharp || flag->zero || flag->plus || flag->space 
   || flag->width || flag->dot) && (*str == 'c' || *str == 's' || *str == 'p' || *str == 'd' ||
		 *str == 'i' || *str == 'u' || *str == 'x' || *str == 'X'))
      len = format_length(str, args, flag);
   if (flag->min == 1)
         len_flag_min(flag, len);
   if (flag->zero == 1)
   {
      if (flag->width > len)
            flag->middle = flag->width - len;
   }
   if (flag->width && (!flag->min) && (!flag->sharp) && (!flag->zero) && (!flag->plus))
      len_flag_width(flag, len);
   if (flag->dot && flag->zero)
   {
      if (flag->dotvalue > len)
         flag->front = flag->width - flag->dotvalue - flag->neg;
      else
         flag->front = flag->width - len - flag->neg;
   }
   if (flag->dot)
      len_flag_dot(flag, len);
}
