/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_radix_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfasius <dfasius@student.42.sg>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 19:12:15 by dfasius           #+#    #+#             */
/*   Updated: 2024/07/25 19:15:52 by dfasius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

int	howmany(t_push *push, int num, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < push->asize)
	{
		if ((push->stacka[i])[num] == c)
			j++;
		i++;
	}
	return (j);
}

int	howmanyb(t_push *push, int num, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < push->bsize)
	{
		if ((push->stackb[i])[num] == c)
			j++;
		i++;
	}
	return (j);
}

int	isthere(t_push *push, int num, char c)
{
	int	i;

	i = 0;
	while (i < push->asize)
	{
		if ((push->stacka[i])[num] == c)
			return (1);
		i++;
	}
	return (0);
}

int	isthereb(t_push *push, int num, char c)
{
	int	i;

	i = 0;
	while (i < push->bsize)
	{
		if ((push->stackb[i])[num] == c)
			return (1);
		i++;
	}
	return (0);
}

int	max_base4(int num)
{
	int	i;

	i = 0;
	while (num > 0)
	{
		num = num / 4;
		i++;
	}
	return (i);
}
