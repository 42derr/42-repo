/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfasius <dfasius@student.42.sg>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 18:10:22 by dfasius           #+#    #+#             */
/*   Updated: 2024/06/06 17:53:51 by dfasius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include "../ft_printf.h"

void	ft_putnbr(long n, int *i, t_flag *flag)
{
	if (n < 0)
	{
		ft_putchar ('-', i);
		ft_putnbr (-n, i, flag);
	}
	else if (n > 9)
	{
		ft_putnbr (n / 10, i, flag);
		ft_putnbr (n % 10, i, flag);
	}
	else
	{
		ft_putchar (n + 48, i);
	}
}

void	ft_putnbr_helper(int n, int *i, t_flag *flag)
{
	long	num;

	num = (long)n;
	if (num == 0 && flag->dot && !flag->dotvalue)
		return ;
	if (num > 2147483647 || num < -2147483648)
		return ;
	if (num >= 0 && flag->space)
		ft_putchar (' ', i);
	if (num >= 0 && flag->plus)
		ft_putchar ('+', i);
	if (num < 0 && (flag->dot || flag->zero))
	{
		ft_putchar ('-', i);
		num *= -1;
	}
	while (flag->middle > 0 && flag->zero == 1)
	{
		ft_putchar ('0', i);
		flag->middle--;
	}
	ft_putnbr (num, i, flag);
}
