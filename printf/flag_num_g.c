/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_num_f.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfasius <dfasius@student.42.sg>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 17:41:02 by dfasius           #+#    #+#             */
/*   Updated: 2024/05/22 18:07:59 by dfasius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include "libprint.h"
#include <stdio.h>

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

void	ft_num_gp(double num, int n)
{
	char	*str;
	int	idx;
	int max;
	int	i;

	i = 0;
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
	ft_putchar_fd (str[0], 1);
	ft_putchar_fd ('.', 1);
	while (idx-- && str[i + 1])
	{
		ft_putchar_fd (str[i + 1], 1);
		i++;
	}
}

void	ft_num_gn(double num, int n)
{
	char	*str;
	int	idx;
	int max;
	int	i;

	i = 0;
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
	ft_putchar_fd ('0', 1);
	ft_putchar_fd ('.', 1);
	while (idx-- && str[i + 1])
	{
		ft_putchar_fd (str[i], 1);
		i++;
	}
}

char	*ft_num_g_small(char *ptr, double num, int n)
{
	if (num > 0)
		ft_num_gp(num, n);
	else if (num < 0)
		ft_num_gn(num, n);
	else if (num == NAN_VAL)
		ft_putstr_fd("-nan", 1);
	else if (num == POS_INF)
		ft_putstr_fd("inf", 1);
	else if (num == NEG_INF)
		ft_putstr_fd("-inf", 1);
	return (ptr + 1);
}

char	*ft_num_g_big(char *ptr, double num, int n)
{
	if (num > 0)
		ft_num_gp(num, n);
	else if (num < 0)
		ft_num_gn(num, n);
	else if (num == NAN_VAL)
		ft_putstr_fd("-NAN", 1);
	else if (num == POS_INF)
		ft_putstr_fd("INF", 1);
	else if (num == NEG_INF)
		ft_putstr_fd("-INF", 1);
	return (ptr + 1);
}