/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_move.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfasius <dfasius@student.42.sg>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 15:57:10 by dfasius           #+#    #+#             */
/*   Updated: 2024/08/19 15:57:11 by dfasius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	num_len(int num)
{
	int	i;

	i = 0;
	if (num == 0)
		return (1);
	while (num > 0)
	{
		num = num / 10;
		i++;
	}
	return (i);
}

void	display_move(t_var *data)
{
	char	*number;
	int		last;
	int		move;

	if (data->string_move)
		free(data->string_move);
	move = data->move;
	last = num_len(move);
	number = (char *)malloc(sizeof(char) * (last + 2));
	if (!number)
		close_window(data);
	number[last + 1] = '\0';
	number[last] = '\n';
	last--;
	while (last >= 0)
	{
		number[last] = (move % 10) + 48;
		move = move / 10;
		last--;
	}
	data->string_move = ft_strjoin("Movement = ", number);
	free(number);
	if (!data->string_move)
		close_window(data);
	ft_putstr_fd(data->string_move, 1);
}
