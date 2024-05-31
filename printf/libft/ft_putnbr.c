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
#include "libft/libft.h"

void	ft_putnbr(int n, int *i)
{
	if (n == -2147483648)
	{
		ft_putchar ('-', i);
		ft_putchar ('2', i);
		ft_putnbr (147483648, i);
	}
	else if (n < 0)
	{
		ft_putchar ('-', i);
		ft_putnbr (-n, i);
	}
	else if (n > 9)
	{
		ft_putnbr (n / 10, i);
		ft_putnbr (n % 10, i);
	}
	else
	{
		ft_putchar (n + 48, i);
	}
}