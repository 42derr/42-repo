/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   il_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfasius <dfasius@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 21:56:02 by dfasius           #+#    #+#             */
/*   Updated: 2024/08/12 20:00:04 by dfasius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pushswap.h"

void	ils_start(t_push *push, int i, int *hun)
{
	int	o;

	o = 0;
	if (!isthere(push, 15 - i, '1'))
		*hun = push->asize;
	while (push->asize > 0 && isthere(push, 15 - i, '0') && *hun == 0)
	{
		if (((push->stacka[push->asize - 1]))[15 - i] == '0')
			cmd_pb(push);
		else
		{
			o++;
			cmd_ra(push, 1);
		}
	}
	fix_loop(push, o);
}

void	ils_one_helper(t_push *push, int i, int *hun, int max)
{
	if (max < 5 && max > 3 && push->asize + push->bsize != 100)
	{
		while (push->bsize > 0
			&& ((push->stackb[push->bsize - 1]))[15 - i] == '0'
			&& ((push->stackb[push->bsize - 1]))[15 - (i - 1)] == '0'
			&& ((push->stackb[push->bsize - 1]))[15 - (i - 1)] != '2')
		{
			cmd_pa(push);
			(*hun)++;
		}
	}
}

void	ils_one(t_push *push, int i, int *hun, int max)
{
	if (max < 4 || push->asize + push->bsize == 100)
	{
		while (push->bsize > 0
			&& ((push->stackb[push->bsize - 1]))[15 - i] == '0')
		{
			cmd_pa(push);
			(*hun)++;
		}
	}
	ils_one_helper(push, i, hun, max);
	while (push->bsize > 0 && isthereb(push, 15 - i, '1'))
	{
		if (((push->stackb[push->bsize - 1]))[15 - (i - 1)] == '0')
			break ;
		if (((push->stackb[push->bsize - 1]))[15 - i] == '1')
			cmd_pa(push);
		else
			cmd_rb(push, 1);
	}
}

void	ils_zero(t_push *push, int i, int *o)
{
	int	max;

	max = push->bsize - howmanyb(push, 15 - i, '1');
	while (push->bsize > 0
		&& ((push->stackb[push->bsize - 1]))[15 - (i - 1)] == '0')
	{
		if (((push->stackb[push->bsize - 1]))[15 - i] == '1')
		{
			cmd_pa(push);
			if (ils_zero_helper(push, i, o, &max))
				break ;
		}
		else
		{
			if (max == 0)
				break ;
			cmd_rb(push, 1);
		}
	}
}

void	ils_adjust(t_push *push, int o, int hun)
{
	if (push->asize - (o + hun) > (o + hun) && push->bsize != 0)
	{
		while (o--)
			cmd_rra(push, 1);
		while (hun--)
			cmd_rra(push, 1);
	}
	else if (push->bsize != 0)
	{
		o = push->asize - o - hun;
		while (o--)
			cmd_ra(push, 1);
	}
}
