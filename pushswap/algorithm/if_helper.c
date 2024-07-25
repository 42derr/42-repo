/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   if_helper.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfasius <dfasius@student.42.sg>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 21:29:49 by dfasius           #+#    #+#             */
/*   Updated: 2024/07/22 21:48:44 by dfasius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pushswap.h"

void	if_three_two(t_push *push, int i)
{
	if ((push->stacka[push->asize - 1])[15 - (i - 1)] == '1')
	{
		cmd_pb(push);
		if (push->asize != 0 && (iz_check_top(push, i, '2', '3')))
			cmd_rr(push);
		else
			cmd_rb(push, 1);
	}
	else if ((push->stacka[push->asize - 1])[15 - (i - 1)] == '2')
	{
		cmd_pb(push);
	}
	else
	{
		cmd_ra(push, 1);
	}
}

void	if_three(t_push *push, int i)
{
	while (push->asize != 0)
	{
		if (((push->stacka[push->asize - 1]))[15 - i] == '2')
			if_three_two(push, i);
		else if (((push->stacka[push->asize - 1]))[15 - i] == '3')
			cmd_pb(push);
		if (!iz_break(push, '2', '2', i)
			&& !iz_break(push, '2', '1', i)
			&& !iz_break(push, '3', '0', i))
			break ;
	}
	while ((iz_check_topb(push, i, '3', '0'))
		|| (iz_check_topb(push, i, '2', '2')))
	{
		cmd_pa(push);
		if ((iz_check_top(push, i, '3', '0')))
			cmd_ra(push, 1);
	}
	while (iz_check_botb(push, i, '2', '1'))
	{
		cmd_rrb(push, 1);
		cmd_pa(push);
	}
}

void	if_two(t_push *push, int i)
{
	while (1)
	{
		if (((push->stackb[push->bsize - 1]))[15 - i] == '2')
			cmd_pa(push);
		else if (((push->stackb[push->bsize - 1]))[15 - i] == '3')
		{
			cmd_pa(push);
			if ((iz_check_topb(push, i, '1', '2')))
				cmd_rr(push);
			else
				cmd_ra(push, 1);
		}
		else
			cmd_rb (push, 1);
		if (!iz_breakb(push, '2', '0', i) && !iz_breakb(push, '3', '1', i))
			break ;
	}
	while ((iz_check_topb(push, i, '1', '2')))
		cmd_rb(push, 1);
	while ((iz_check_botb(push, i, '1', '2'))
		|| (iz_check_botb(push, i, '1', '3')))
		cmd_rrb(push, 1);
	while ((iz_check_topb(push, i, '1', '2'))
		|| (iz_check_topb(push, i, '1', '3')))
		cmd_pa(push);
}

void	if_one_helper(t_push *push, int i)
{
	while ((iz_check_botb(push, i, '1', '0'))
		|| (iz_check_botb(push, i, '0', '3')))
	{
		if (iz_check_botb(push, i, '0', '3'))
			cmd_rrb(push, 1);
		else
		{
			cmd_rrb(push, 1);
			cmd_pa(push);
		}
	}
	while (iz_check_topb(push, i, '0', '3'))
		cmd_pa(push);
}

void	if_one(t_push *push, int i)
{
	while (1)
	{
		if ((iz_check_topb(push, i, '1', '1')))
			cmd_pa(push);
		else if (((push->stackb[push->bsize - 1]))[15 - i] == '3')
		{
			cmd_pa(push);
			if ((iz_check_topb(push, i, '1', '0'))
				|| (iz_check_topb(push, i, '0', '3')))
				cmd_rr(push);
			else
				cmd_ra(push, 1);
		}
		else
			cmd_rb (push, 1);
		if (!iz_breakb(push, '1', '1', i) && !iz_breakb(push, '3', '2', i))
			break ;
	}
	while ((iz_check_topb(push, i, '1', '0'))
		|| (iz_check_topb(push, i, '0', '3')))
		cmd_rb(push, 1);
	if_one_helper(push, i);
}
