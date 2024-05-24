/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_num_g.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfasius <dfasius@student.42.sg>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 17:41:02 by dfasius           #+#    #+#             */
/*   Updated: 2024/05/24 20:08:42 by dfasius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft/libft.h"
#include "ft_printf.h"
#include <math.h>

void	ft_num_gp(double num, int n, int *i)
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
	while ((int)num % 10 == 0)
		num = num / 10;
	str = ft_itoa((int)num);
	ft_putchar_fd (str[0], 1, i);
	ft_putchar_fd ('.', 1, i);
	while (idx-- && str[x + 1])
	{
		ft_putchar_fd (str[x + 1], 1, i);
		i++;
	}
}

void	ft_num_gn(double num, int n, int *i)
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
	while ((int)num % 10 == 0)
		num = num / 10;
	str = ft_itoa((int)num);
	ft_putchar_fd ('0', 1, i);
	ft_putchar_fd ('.', 1, i);
	while (idx-- && str[x + 1])
	{
		ft_putchar_fd (str[x], 1, i);
		x++;
	}
}

char	*ft_num_g_small(char *ptr, double num, int n, int *i)
{
	if (num >= 1)
		ft_num_gp(num, n, i);
	else if (num < 1)
		ft_num_gn(num, n, i);
	else if (num == NAN)
		ft_putstr_fd("-nan", 1, i);
	else if (num == INFINITY)
		ft_putstr_fd("inf", 1, i);
	else if (num == -INFINITY)
		ft_putstr_fd("-inf", 1, i);
	return (ptr + 1);
}

char	*ft_num_g_big(char *ptr, double num, int n, int *i)
{
	if (num >= 1)
		ft_num_gp(num, n, i);
	else if (num < 1)
		ft_num_gn(num, n, i);
	else if (num == NAN)
		ft_putstr_fd("-NAN", 1, i);
	else if (num == INFINITY)
		ft_putstr_fd("INF", 1, i);
	else if (num == -INFINITY)
		ft_putstr_fd("-INF", 1, i);
	return (ptr + 1);
}
