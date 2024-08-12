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
#include <stdio.h>

void	i_last_spes(t_push *push, int i, int max)
{
	int	hun;
	int	o;

	i++;
	hun = 0;
	o = 0;
	ils_start(push, i, &hun);
	ils_one(push, i, &hun, max);
	int d = 0;
	while (d < push->asize)
	{
		printf("%s\n", push->stacka[d]);
		d++;
	}
	printf("\n");
	 d = 0;
	while (d < push->bsize)
	{
		printf("%s\n", push->stackb[d]);
		d++;
	}
	printf("\n");
	printf("\n");
	ils_zero(push, i, &o);
	ils_adjust(push, o, hun);
		 d = 0;
	while (d < push->asize)
	{
		printf("%s\n", push->stacka[d]);
		d++;
	}
	printf("\n");
	 d = 0;
	while (d < push->bsize)
	{
		printf("%s\n", push->stackb[d]);
		d++;
	}
	ils_finish(push, i);
	free_all(push);
	exit(0);
}
