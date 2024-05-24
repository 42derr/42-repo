/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfasius <dfasius@student.42.sg>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 18:10:22 by dfasius           #+#    #+#             */
/*   Updated: 2024/05/19 15:29:24 by dfasius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <unistd.h>

static void	ft_putchar_fd(char c, int fd, int *i)
{
	*i += write (fd, &c, 1);
}

void	ft_putnbr_fd(int n, int fd, int *i)
{
	if (n == -2147483648)
	{
		ft_putchar_fd ('-', fd, i);
		ft_putchar_fd ('2', fd, i);
		ft_putnbr_fd (147483648, fd, i);
	}
	else if (n < 0)
	{
		ft_putchar_fd ('-', fd, i);
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
/*
int	main(void)
{
	ft_putnbr_fd(-123456789,1);
}
*/
