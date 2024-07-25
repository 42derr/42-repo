/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ir_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfasius <dfasius@student.42.sg>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 17:50:07 by dfasius           #+#    #+#             */
/*   Updated: 2024/07/25 17:55:23 by dfasius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pushswap.h"

void	fix_loop_return(t_push *push, int o)
{
	if (push->bsize > 1 && o != 0)
	{
		o = push->bsize % o;
		while (o--)
			cmd_rrb(push, 1);
	}
}

void	i_return_spes(t_push *push, int i, int *o)
{
	while ((isthereb(push, 15 - i, '0')) || (isthereb(push, 15 - i, '1'))
		|| (isthereb(push, 15 - i, '2')))
	{
		if ((isthereb(push, 15 - i, '1') || isthereb(push, 15 - i, '2')))
			cmd_pa(push);
		else
		{
			if (((push->stackb[0]))[15 - (i + 1)] == '0')
			{
				(*o)++;
				cmd_rrb(push, 1);
			}
			else
			{
				cmd_rrb(push, 1);
				cmd_pa(push);
			}
			if (!(isthereb(push, 15 - (i + 1), '1'))
				&& !(isthereb(push, 15 - (i + 1), '2'))
				&& !(isthereb(push, 15 - (i + 1), '3')))
				break ;
		}
	}
}

void	i_return(t_push *push, int i, int max)
{
	int	o;

	o = 0;
	if (i < max - 2 && i >= 2)
	{
		i_return_spes(push, i, &o);
		fix_loop_return(push, o);
	}
	else
	{
		while (push->bsize != 0 && i != 0 && i != 1)
		{
			if ((isthereb(push, 15 - i, '1') || isthereb(push, 15 - i, '2')))
				cmd_pa(push);
			else if (push->bsize > 1)
			{
				cmd_rrb(push, 1);
				cmd_pa(push);
			}
			else
				cmd_pa(push);
		}
	}
}
