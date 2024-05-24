/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_num_e.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfasius <dfasius@student.42.sg>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 17:41:02 by dfasius           #+#    #+#             */
/*   Updated: 2024/05/24 20:52:23 by dfasius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft/libft.h"
#include "ft_printf.h"
#include <math.h>

void	ft_num_eplen(double num, int *i)
{
	int	number;
	int	x;

	number = (int) num;
	x = 0;
	while (number > 9)
	{
		number = number / 10;
		x++;
	}
	if (x < 10)
	{
		ft_putchar_fd ('0', 1, i);
		ft_putchar_fd (x + '0', 1, i);
	}
	else
	{
		ft_putstr_fd (ft_itoa(x), 1, i);
	}
}

void	ft_num_enlen(double num, int *i)
{
	int	x;

	x = 0;
	while ((int) num < 1)
	{
		num = num * 10;
		x++;
	}
	if (x < 10)
	{
		ft_putchar_fd ('0', 1, i);
		ft_putchar_fd (x + '0', 1, i);
	}
	else
	{
		ft_putstr_fd (ft_itoa(x), 1, i);
	}
}

void	ft_num_ep(double num, int n, int *i)
{
	char	*str;
	int		idx;
	int		max;
	int		x;

	x = 0;
	if (n != 0)
		idx = n;
	else
		idx = 6;
	max = maxval(idx);
	while ((int) num < max)
		num = num * 10;
	str = ft_itoa((int)num);
	ft_putchar_fd (str[0], 1, i);
	ft_putchar_fd ('.', 1, i);
	while (idx--)
	{
		ft_putchar_fd (str[x + 1], 1, i);
		i++;
	}
}

char	*ft_num_e_small(char *ptr, double num, int n, int *i)
{
	if (num >= 1)
	{
		ft_num_ep(num, n, i);
		ft_putstr_fd ("+e", 1, i);
		ft_num_eplen (num, i);
	}
	else if (num < 1)
	{
		ft_num_ep(num, n, i);
		ft_putstr_fd ("-e", 1, i);
		ft_num_enlen (num, i);
	}
	else if (num == NAN)
		ft_putstr_fd("-nan", 1, i);
	else if (num == INFINITY)
		ft_putstr_fd("inf", 1, i);
	else if (num == -INFINITY)
		ft_putstr_fd("-inf", 1, i);
	return (ptr + 1);
}

char	*ft_num_e_big(char *ptr, double num, int n, int *i)
{
	if (num >= 1)
	{
		ft_num_ep(num, n, i);
		ft_putstr_fd ("+E", 1, i);
		ft_num_eplen (num, i);
	}
	else if (num < 1)
	{
		ft_num_ep(num, n, i);
		ft_putstr_fd ("-E", 1, i);
		ft_num_enlen (num, i);
	}
	else if (num == NAN)
		ft_putstr_fd("-NAN", 1, i);
	else if (num == INFINITY)
		ft_putstr_fd("INF", 1, i);
	else if (num == -INFINITY)
		ft_putstr_fd("-INF", 1, i);
	return (ptr + 1);
}
