/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_radix_sort.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfasius <dfasius@student.42.sg>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 19:07:43 by dfasius           #+#    #+#             */
/*   Updated: 2024/07/25 19:11:56 by dfasius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

char	*base4_string(int num)
{
	char	*str;
	int		i;

	i = 15;
	str = (char *)malloc (sizeof(char) * 17);
	str[16] = '\0';
	while (num > 0 && i >= 0)
	{
		str[i] = (num % 4) + '0';
		num = num / 4;
		i--;
	}
	while (i >= 0)
	{
		str[i] = '0';
		i--;
	}
	return (str);
}

char	**base4_array(t_push *push)
{
	char	**buffer;
	int		i;

	i = 0;
	buffer = (char **) malloc (sizeof(char *) * (push->asize + 1)); //this
	if (!buffer)
		return (0);
	while (i < push->asize)
	{
		buffer[i] = base4_string(push->astart[i]);
		i++;
	}
	buffer[i] = 0;
	return (buffer);
}

void	radix_base4(t_push *push)
{
	int	i;
	int	max;

	push->stacka = base4_array(push);
	push->stackb = (char **) malloc (sizeof(char *) * (push->asize + 1));
	i = 0;
	max = max_base4(push->asize - 1);
	while (i < max)
	{
		if (i == 0)
		{
			i_zero(push, &i);
			i_first(push, i);
			i = 1;
		}
		else
			i_normal(push, i);
		if (i == max - 2 && !(isthere(push, 15 - (max - 1), '2'))
			&& !(isthere(push, 15 - (max - 1), '3')))
			i_last_spes(push, i, max);
		i_return (push, i, max);
		i++;
	}
}
