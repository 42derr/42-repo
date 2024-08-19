/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfasius <dfasius@student.42.sg>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 18:29:58 by dfasius           #+#    #+#             */
/*   Updated: 2024/08/19 18:29:59 by dfasius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

int	main(int agrc, char **argv)
{
	t_map	map;

	map = (t_map){0};
	if (agrc != 2)
		return (ft_putstr_fd("Error\n./so_long mapname.ber\n", 2), 1);
	read_map(&map, argv[1]);
	visual (&map);
}
