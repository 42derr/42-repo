/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_asg.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfasius <dfasius@student.42.sg>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 18:27:04 by dfasius           #+#    #+#             */
/*   Updated: 2024/07/25 18:53:41 by dfasius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

int	assign_stacka(int argc, char **argv, t_push *push)
{
	int	max;
	int	i;

	if (check_argv(argc, argv) == 0)
	{
		ft_putstr_fd("Error\n", 2);
		return (0);
	}
	max = argc - 1;
	i = 1;
	push->astart = (int *) malloc(sizeof(int) * (argc - 1));
	if (!push->astart)
		return (0);
	while (max)
	{
		push->astart[max - 1] = ft_atol(argv[i]);
		max--;
		i++;
	}
	push->asize = argc - 1;
	if (!reassign_stacka(push))
		return (0);
	return (1);
}

int	reassign_stacka(t_push *push)
{
	int	i;
	int	j;
	int	c;
	int	*newstack;

	newstack = (int *) malloc(sizeof(int) * push->asize);
	if (!newstack)
		return (free(push->astart), 0);
	i = 0;
	while (i < push->asize)
	{
		j = 0;
		c = 0;
		while (j < push->asize)
		{
			if (push->astart[i] > push->astart[j])
				c++;
			j++;
		}
		newstack[i] = c;
		i++;
	}
	free(push->astart);
	push->astart = newstack;
	return (1);
}

int	assign_stackb(int argc, t_push *push)
{
	push->bstart = (int *) malloc(sizeof(int) * (argc - 1));
	if (!push->bstart)
	{
		free(push->astart);
		return (0);
	}
	push->bsize = 0;
	return (1);
}
