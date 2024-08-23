/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfasius <dfasius@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 15:57:14 by dfasius           #+#    #+#             */
/*   Updated: 2024/08/23 09:29:51 by dfasius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	map_err(t_map *map, char *buffer, char *err, char *str_err)
{
	ft_putstr_fd("Error\n", 2);
	if (err)
		perror(err);
	if (str_err)
		ft_putstr_fd(str_err, 2);
	if (map && map->map_lst)
		ft_lstclear(&map->map_lst, &free);
	if (buffer)
		free(buffer);
	if (map && map->amap)
		free_array(map->amap);
	exit (1);
}

void	tex_err(char *buffer)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(buffer, 2);
	ft_putstr_fd("\n", 2);
}
void	free_array(char	**buffer)
{
	int	i;

	i = 0;
	while (buffer[i])
	{
		free(buffer[i]);
		i++;
	}
	free(buffer);
}

void	free_bool(bool	**buffer, int j)
{
	int	i;

	i = 0;
	while (i < j)
	{
		free(buffer[i]);
		i++;
	}
	free(buffer);
}
