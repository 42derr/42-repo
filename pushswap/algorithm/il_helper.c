/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   il_helper.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfasius <dfasius@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 21:50:48 by dfasius           #+#    #+#             */
/*   Updated: 2024/08/12 19:51:25 by dfasius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pushswap.h"

void	ils_finish(t_push *push, int i)
{
	while (push->bsize > 0 && isthereb(push, 15 - i, '0'))
	{
		if (((push->stackb[push->bsize - 1]))[15 - i] == '0')
			cmd_pa(push);
		if (((push->stackb[push->bsize - 1]))[15 - (i - 1)] == '0')
			break ;
	}
	while (push->bsize > 0)
	{
		if (push->bsize > 1)
		{
			cmd_rrb(push, 1);
			cmd_pa(push);
		}
		else
			cmd_pa(push);
	}
}

int	ils_zero_helper(t_push *push, int i, int *o, int *max)
{
	if (((push->stackb[push->bsize - 1]))[15 - i] == '1')
	{
		cmd_ra(push, 1);
		(*o)++;
		(*max)--;
	}
	else
	{
		if (!(((push->stackb[push->bsize - 1]))[15 - (i - 1)] == '0'))
			return (1);
		if (*max == 0)
			return (1);
		cmd_rr(push);
		(*o)++;
		(*max)--;
	}
	return (0);
}

void	i_last_spes(t_push *push, int i, int max)
{
	int	hun;
	int	o;

	if (push->asize + push->bsize <= 128
		|| (push->asize + push->bsize >= 177
			&& push->asize + push->bsize <= 512))
	{
		i++;
		hun = 0;
		o = 0;
		ils_start(push, i, &hun);
		ils_one(push, i, &hun, max);
		ils_zero(push, i, &o);
		ils_adjust(push, o, hun);
		ils_finish(push, i);
		free_all(push);
		exit(0);
	}
}
