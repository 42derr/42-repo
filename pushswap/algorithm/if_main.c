/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   if_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfasius <dfasius@student.42.sg>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 21:47:57 by dfasius           #+#    #+#             */
/*   Updated: 2024/07/22 21:55:48 by dfasius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pushswap.h"

void	if_zero_helper(t_push *push, int i)
{
	while (iz_breakb(push, '0', '1', i))
	{
		if ((iz_check_topb(push, i, '0', '0')))
			cmd_rb(push, 1);
		else
			cmd_pa(push);
	}
	while (push->bsize != 0)
		cmd_pa(push);
}

void	if_zero(t_push *push, int i)
{
	while (1)
	{
		if ((iz_check_topb(push, i, '0', '2')))
			cmd_pa(push);
		else if (((push->stackb[push->bsize - 1]))[15 - i] == '3')
		{
			cmd_pa(push);
			if ((iz_check_topb(push, i, '0', '0'))
				|| (iz_check_topb(push, i, '0', '1')))
				cmd_rr(push);
			else
				cmd_ra(push, 1);
		}
		else
			cmd_rb (push, 1);
		if (!iz_breakb(push, '0', '2', i) && !iz_breakb(push, '3', '3', i))
			break ;
	}
	if_zero_helper(push, i);
}

void	i_first(t_push *push, int i)
{
	if_three(push, i);
	if_two(push, i);
	if_one(push, i);
	if_zero(push, i);
}

int	iz_breakb(t_push *push, int cf, int ct, int is)
{
	int	i;

	i = 0;
	while (i < push->bsize)
	{
		if ((push->stackb[i])[15 - is] == cf
			&& (push->stackb[i])[15 - (is - 1)] == ct)
			return (1);
		i++;
	}
	return (0);
}
