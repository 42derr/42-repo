/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfasius <dfasius@student.42.sg>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 13:38:09 by dfasius           #+#    #+#             */
/*   Updated: 2024/05/21 19:26:01 by dfasius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include "libft.h"
#include <unistd.h>
// flag -, +,  , #, 0, . , number;
//
void	ft_putusnbr(unsigned int nbr)
{
	if (nbr > 9)
	{
		ft_putusnbr(nbr / 10);
		ft_putusnbr(nbr % 10);
	}
	else
	{
		ft_putchar_fd(nbr + '0', 1);
	}
}

void	ft_puthex(unsigned int nbr)
{
	char	c;

	if (nbr > 15)
	{
		ft_puthex(nbr / 16);
	        ft_puthex(nbr % 16);	
	}
	else
	{
		c = "0123456789abcdef"[nbr];
		ft_putchar_fd(c , 1);
	}
}

void	ft_puthex_addr(long nbr)
{
	char	c;

	if (nbr > 15)
	{
		ft_puthex_addr(nbr / 16);
	        ft_puthex_addr(nbr % 16);	
	}
	else
	{
		c = "0123456789abcdef"[nbr];
		ft_putchar_fd(c , 1);
	}
}

void	ft_putaddr(void *add)
{
	long nbr;

	nbr = (long) add;
	write (1, "0", 1);
	write (1, "x", 1);
	ft_puthex_addr(nbr);
}

void	ft_puthex_big(unsigned int nbr)
{
	char	c;

	if (nbr > 15)
	{
		ft_puthex_big(nbr / 16);
	        ft_puthex_big(nbr % 16);
	}
	else
	{
		c = "0123456789ABCDEF"[nbr];
		ft_putchar_fd(c , 1);
	}
}

char	*format_check(char *str, va_list args)
{
	if (*str == 'c')
		ft_putchar_fd(va_arg(args, int), 1);
	else if (*str == 's')
		ft_putstr_fd(va_arg(args, char *), 1);
	else if (*str == 'p')
		ft_putaddr(va_arg(args, void *));
	else if (*str == 'd')
		ft_putnbr_fd(va_arg(args, int), 1);
	else if (*str == 'i')
		return (0);
	else if (*str == 'u')
		ft_putusnbr(va_arg(args, unsigned int));
	else if (*str == 'x')
		ft_puthex(va_arg(args, unsigned int));
	else if (*str == 'X')
		ft_puthex_big(va_arg(args, unsigned int));
	else if (*str == '%')
		write(1, "%", 1);
	return (0);
}

int	flag_min_len(char *str, va_list args)
{
	while (*str == '-' || *str >= '0' && *str <= '9')
		str++;
	if (*str == 'c')
		return (1);
	else if (*str == 's')
		return (ft_strlen(va_arg(args, char *)));
	else if (*str == 'p')
		return (0);
	else if (*str == 'd')
		return (ft_strlen(ft_itoa(va_arg(args, int))));
	else if (*str == 'i')
		return (0);
	else if (*str == 'u')
		return (0);
	else if (*str == 'x')
		return (0);
	else if (*str == 'X')
		return (0);
	else if (*str == '%')
		return (1);
	return (0);
}

int	flag_zero_len(char *str, va_list args)
{
	while (*str == '0' || *str >= '0' && *str <= '9')
		str++;
	if (*str == 'c')
		return (1);
	else if (*str == 's')
		return (ft_strlen(va_arg(args, char *)));
	else if (*str == 'p')
		return (0);
	else if (*str == 'd')
		return (ft_strlen(ft_itoa(va_arg(args, int))));
	else if (*str == 'i')
		return (0);
	else if (*str == 'u')
		return (0);
	else if (*str == 'x')
		return (0);
	else if (*str == 'X')
		return (0);
	else if (*str == '%')
		return (1);
	return (0);
}

char	*flag_min(char *str, va_list args)
{
	int	cur;
	int	print;
	va_list	args2;

	va_copy (args2, args);
	cur = flag_min_len(str, args);
	print = 0;
	while (*str == '-')
		str++;
	print = ft_atoi (str);
	while (*str >= '0' && *str <= '9')
		str++;
	if (print > cur)
		print = print - cur;
	else
		print = 0;
	format_check(str, args2);
	str++;
	while (print--)
		ft_putchar_fd(' ',1);
	return (str);
}

char	*flag_zero(char *str, va_list args)
{
	int	cur;
	int	print;
	va_list args2;

	va_copy (args2,args);
	cur = flag_zero_len(str, args);
	print = 0;
	while (*str == '0')
		str++;
	print = ft_atoi (str);
	while (*str >= '0' && *str <= '9')
		str++;
	if (print > cur)
		print = print - cur;
	else
		print = 0;
	while (print--)
		ft_putchar_fd('0',1);
	format_check(str, args2);
	str++;
	return (str);
}

char	*flag_plus(char *str, va_list args)
{
	va_list args2;

	va_copy (args2, args);
	while (*str == '+')
		str++;
	if (va_arg(args, int) >= 0)
		ft_putchar_fd ('+', 1);
	format_check(str, args2);
	str++;
	return (str);
}

char	*flag_space(char *str, va_list args)
{
	while (*str == ' ')
		str++;
	ft_putchar_fd (' ', 1);
	format_check(str, args);
	str++;
	return (str);
}

char	*flag_number(char *str)
{
	return (0);
}

char	*flag_width(char *str)
{
	return (0);
}


char	*flag_check(char *str, va_list args)
{
	if (*str == '-')
		return (flag_min(str, args));
	else if (*str == '+')
		return (flag_plus(str, args));
	else if (*str == ' ')
		return (flag_space(str, args));
	else if (*str == '#')
		return (flag_number(str));
	else if (*str == '0')
		return (flag_zero(str, args));
	else if (*str >= '1' && *str <= '9')
		return (flag_width(str));
	return (0);
}

int	ft_printf(const char *str, ...)
{
	va_list args;
	char	*ptr;
	char	*ptr2;

	va_start (args, str);
	ptr = (char *) str;
	while (*ptr)
	{
		if (*ptr == '%')
		{
			ptr2 = ptr;
			ptr = flag_check (ptr + 1, args);
			if (!ptr)
			{
				ptr = ptr2 + 1;
				format_check(ptr, args);
				ptr++;
			}
		}
		if (*ptr == '\0')
			return (0);
		ft_putchar_fd(*ptr, 1);
		ptr++;
	}
	va_end(args);
	return (0);
}

int     main(void)
{
	ft_putaddr(16);
        //ft_printf("%d", 123);
        //printf("%d\n",10);
}

