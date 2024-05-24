/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_num_f.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfasius <dfasius@student.42.sg>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 17:41:02 by dfasius           #+#    #+#             */
/*   Updated: 2024/05/24 20:08:12 by dfasius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft/libft.h"
#include "ft_printf.h"
#include <math.h>

int	maxval(int size)
{
	int	store;

	store = 1;
	while (size--)
	{
		store = store * 10;
	}
	return (store);
}

void	ft_num_fp(double num, int n, int *i)
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

void	ft_num_fn(double num, int n, int *i)
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
	ft_putchar_fd ('0', 1, i);
	ft_putchar_fd ('.', 1, i);
	while (idx--)
	{
		ft_putchar_fd (str[x], 1, i);
		i++;
	}
}

char	*ft_num_f_small(char *ptr, double num, int n, int *i)
{
	if (num >= 1)
		ft_num_fp(num, n, i);
	else if (num < 1)
		ft_num_fn(num, n, i);
	else if (num == NAN)
		ft_putstr_fd("-nan", 1, i);
	else if (num == INFINITY)
		ft_putstr_fd("inf", 1, i);
	else if (num == -INFINITY)
		ft_putstr_fd("-inf", 1, i);
	return (ptr + 1);
}

char	*ft_num_f_big(char *ptr, double num, int n, int *i)
{
	if (num >= 1)
		ft_num_fp(num, n, i);
	else if (num < 1)
		ft_num_fn(num, n, i);
	else if (num == NAN)
		ft_putstr_fd("-NAN", 1, i);
	else if (num == INFINITY)
		ft_putstr_fd("INF", 1, i);
	else if (num == -INFINITY)
		ft_putstr_fd("-INF", 1, i);
	return (ptr + 1);
}
