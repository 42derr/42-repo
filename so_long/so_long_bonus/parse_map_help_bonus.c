/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_help_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfasius <dfasius@student.42.sg>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 18:30:06 by dfasius           #+#    #+#             */
/*   Updated: 2024/08/19 18:30:07 by dfasius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	map_info(t_map *map, t_list *maplist, int i)
{
	int	j;

	j = 0;
	while (j < map->width)
	{
		if (((char *)maplist->content)[j] == 'E')
			map->exit++;
		if (((char *)maplist->content)[j] == 'C')
			map->collectible++;
		if (((char *)maplist->content)[j] == 'P')
		{
			map->start++;
			map->playerx = j;
			map->playery = i;
		}
		j++;
	}
}

void	check_map_helper(t_map *map, t_list *maplist, int i)
{
	int	j;

	j = 0;
	if ((int) ft_strlen(maplist->content) != map->width)
		map_err(map, 0, 0, "The map must be rectangular.\n");
	if (i == (map->height - 1) || i == 0)
	{
		j = 0;
		while (j < map->width)
		{
			if (((char *)maplist->content)[j] != '1')
				map_err(map, 0, 0, "The map must be surrounded by walls.\n");
			j++;
		}
	}
	else
		map_info(map, maplist, i);
	if (((char *)maplist->content)[0] != '1'
		|| ((char *)maplist->content)[map->width - 1] != '1')
		map_err(map, 0, 0, "The map must be surrounded by walls.\n");
}

void	check_map(t_map *map)
{
	int		i;
	t_list	*maplist;

	maplist = map->map_lst;
	i = 0;
	while (i < map->height)
	{
		check_map_helper(map, maplist, i);
		i++;
		maplist = maplist->next;
	}
	if (map->start != 1)
		map_err(map, 0, 0, "The map must contain 1 starting position.\n");
	if (map->collectible < 1)
		map_err(map, 0, 0, "The map must contain at least 1 collectible.\n");
	if (map->exit != 1)
		map_err(map, 0, 0, "The map must contain 1 exit\n");
	if (validate_map(map) == false)
		map_err(map, 0, 0, "There is no valid path.\n");
}
