/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pushswap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfasius <dfasius@student.42.sg>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 20:41:06 by dfasius           #+#    #+#             */
/*   Updated: 2024/07/25 19:17:32 by dfasius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

int	main(int argc, char **argv)
{
	t_push	push;

	push = (t_push){0};
	if (argc == 1)
		return (1);
	if (!assign_stacka(argc, argv, &push))
		return (1);
	if (!assign_stackb(argc, &push))
		return (1);
	if (check_stack(&push))
	{
		free(push.astart);
		free(push.bstart);
		return (1);
	}
	solve_stack(&push, argc);
	free_all(&push);
	return (0);
}