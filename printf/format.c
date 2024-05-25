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

char	*format_check(char *str, va_list args, int *i)
{
	if (*str == 'c')
		ft_putchar_fd (va_arg(args, int), 1, i);
	else if (*str == 's')
		ft_putstr_fd (va_arg(args, char *), 1, i);
	else if (*str == 'p')
		ft_putaddr (va_arg(args, void *), i);
	else if (*str == 'd' || *str == 'i')
		ft_putnbr_fd (va_arg(args, int), 1, i);
	else if (*str == 'i')
		ft_putnbr_fd (va_arg(args, int), 1, i);
	else if (*str == 'u')
		ft_putusnbr (va_arg(args, unsigned int), i);
	else if (*str == 'x')
		ft_puthex (va_arg(args, unsigned int), i);
	else if (*str == 'X')
		ft_puthex_big (va_arg(args, unsigned int), i);
	else if (*str == '%')
		ft_putchar_fd('%', 1, i);
	return (0);
}

char	*format_check_space(char *str, va_list args, int *i, int print)
{
	int	num;
	char *string;

	if (*str == 'd' || *str == 'i')
	{
		num = va_arg(args, int);
		if (num >= 0)
			ft_putchar_fd (' ', 1, i);
		ft_putnbr_fd (num, 1, i);
	}
	else if (*str == 's')
	{
		string = va_arg(args, char *);
		while (print != 0)
		{
			ft_putchar_fd (' ', 1, i);
			print--;
		}
		if (string[0] == '\0')
			return (str + 1);
		ft_putstr_fd (string , 1, i);
	}
	return (0);
}

void	ft_putstr_dot(char *s, int fd, int *x, int w)
{
	int	i;

	i = 0;
	if (s == NULL)
	{
		ft_putstr_fd ("(null)", 1, x);
		return ;
	}
	while (s[i] && w != 0)
	{
		*x = *x + 1;
		i++;
		w--;
	}
	write (fd, s, i);
}

char	*format_check_dot(char *str, va_list args, int *i, int w)
{
	if (*str == 'c')
		ft_putchar_fd (va_arg(args, int), 1, i);
	else if (*str == 's')
		ft_putstr_dot (va_arg(args, char *), 1, i, w);
	else if (*str == 'p')
		ft_putaddr (va_arg(args, void *), i);
	else if (*str == 'd' || *str == 'i')
		ft_putnbr_fd (va_arg(args, int), 1, i);
	else if (*str == 'i')
		ft_putnbr_fd (va_arg(args, int), 1, i);
	else if (*str == 'u')
		ft_putusnbr (va_arg(args, unsigned int), i);
	else if (*str == 'x')
		ft_puthex (va_arg(args, unsigned int), i);
	else if (*str == 'X')
		ft_puthex_big (va_arg(args, unsigned int), i);
	else if (*str == '%')
		ft_putchar_fd('%', 1, i);
	return (0);
}

char	*format_check_zero(char *str, va_list args, int *i, int print)
{
	int	num;
	unsigned int numus;

	if (*str == 'd' || *str == 'i')
	{
		num = va_arg(args, int);
		if (num >= 0)
			while(print--)
				ft_putchar_fd('0', 1, i);
		ft_putnbr_zero (num, 1, i, print);
	}
	else if (*str == 'u' || *str == 'x' || *str == 'X')
	{
		numus = va_arg(args, unsigned int);
		while(print--)
			ft_putchar_fd('0', 1, i);
		if (*str == 'u')
		ft_putusnbr (numus, i);
		else if (*str == 'x')
		ft_puthex (numus, i);
		else if (*str == 'X')
		ft_puthex_big (numus, i);
	}
	return (0);
}

void	ft_putnbr_zero(int n, int fd, int *i, int print)
{
	if (n == -2147483648)
	{
		ft_putchar_fd ('-', fd, i);
		while (print--)
			ft_putchar_fd('0', 1, i);
		ft_putchar_fd ('2', fd, i);
		ft_putnbr_fd (147483648, fd, i);
	}
	else if (n < 0)
	{
		ft_putchar_fd ('-', fd, i);
		while (print--)
		ft_putchar_fd('0', 1, i);
		ft_putnbr_fd (-n, fd, i);
	}
	else if (n > 9)
	{
		ft_putnbr_fd (n / 10, fd, i);
		ft_putnbr_fd (n % 10, fd, i);
	}
	else
	{
		ft_putchar_fd (n + 48, fd, i);
	}
}